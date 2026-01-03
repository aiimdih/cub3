
// textured_cub3d.c
// Compile: gcc textured_cub3d.c -lmlx -lXext -lX11 -lm -o textured_cub3d

#include <mlx.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define SCREEN_W 800
#define SCREEN_H 600

#define MAP_W 8
#define MAP_H 8

#define MOVE_SPEED 0.06
#define ROT_SPEED  0.05

// Linux keycodes
#define KEY_ESC   65307
#define KEY_W     119
#define KEY_A     97
#define KEY_S     115
#define KEY_D     100
#define KEY_LEFT  65361
#define KEY_RIGHT 65363

#define TEX_COUNT 5
#define TEX_W 64
#define TEX_H 64

typedef struct s_img {
    void *img;
    char *addr;
    int bpp;
    int line_len;
    int endian;
} t_img;

typedef struct s_game {
    void    *mlx;
    void    *win;
    t_img   screen;
    t_img   tex[TEX_COUNT];

    double  posX, posY;   // player position
    double  dirX, dirY;   // direction vector
    double  planeX, planeY; // camera plane

    // input flags
    int move_w, move_s;
    int move_a, move_d;
    int rot_l, rot_r;
} t_game;

typedef struct s_render {
	double cameraX;
	double rayDirX;
	double rayDirY;
	double deltaDistX;
	double deltaDistY;
	double sideDistX;
	double sideDistY;
	double prepWallDist;
	int texId;
	int texX;
	int drawStart;
	int drawEnd;
	int lineHeight;
	int stepX;
	int stepY;
	int side;
	int mapX;
	int mapY;
} t_render;

typedef struct s_tex {
	int texY;
	double step;
	double texPos;
	double shade;
	double shaded;
	unsigned int color;
	unsigned int r;
	unsigned int gg;
	unsigned int b;
} t_tex;

/* Map:
   0 = empty
   1..5 = wall types -> textures 0..4
*/
int worldMap[MAP_H][MAP_W] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,2,0,0,0,1},
    {1,0,3,0,4,0,0,1},
    {1,0,1,0,0,0,5,1},
    {1,0,2,0,3,4,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

void pixel_put(t_img *img, int x, int y, unsigned int color)
{
    if (!img->addr) return;
    if (x < 0 || y < 0 || x >= SCREEN_W || y >= SCREEN_H) return;
    char *dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

unsigned int tex_pixel(t_img *tex, int x, int y)
{
    if (!tex->addr) return 0;
    if (x < 0) x = 0; if (x >= TEX_W) x = TEX_W - 1;
    if (y < 0) y = 0; if (y >= TEX_H) y = TEX_H - 1;
    char *src = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
    return *(unsigned int *)src;
}

void draw_background(t_game *g)
{
    for (int y = 0; y < SCREEN_H; y++)
    {
        unsigned int color = (y < SCREEN_H/2) ? 0x87CEEB : 0x444444;
        for (int x = 0; x < SCREEN_W; x++)
            pixel_put(&g->screen, x, y, color);
    }
}

void count_delta(t_render *r, t_game *g)
{
	if (r->rayDirX < 0)
	{
		r->stepX = -1;
		r->sideDistX = (g->posX - (int)g->posX) * r->deltaDistX;
	}
	else
	{
		r->stepX = 1;
		r->sideDistX = ((int)g->posX + 1.0 - g->posX) * r->deltaDistX;
	}
	if (r->rayDirY < 0)
	{
		r->stepY = -1;
		r->sideDistY = (g->posY - (int)g->posY) * r->deltaDistY;
	}
	else
	{
		r->stepY = 1;
		r->sideDistY = ((int)g->posY + 1.0 - g->posY) * r->deltaDistY;
	}
}

void dda(t_render *r)
{
	int hit;
	hit = 0;
	while (!hit)
	{
		if (r->sideDistX < r->sideDistY)
		{
			r->sideDistX += r->deltaDistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sideDistY += r->deltaDistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (r->mapX < 0 || r->mapX >= MAP_W || r->mapY < 0 || r->mapY >= MAP_H) { hit = 1; break; }
		if (worldMap[r->mapY][r->mapX] > 0) 
			hit = 1;
	}
}
void compute_perp_wall_dist(t_render *r)
{
	if (r->side == 0)
		r->prepWallDist = r->sideDistX - r->deltaDistX;
	else
		r->prepWallDist = r->sideDistY - r->deltaDistY;
	if (r->prepWallDist < 0.000001)
		r->prepWallDist = 0.000001;
	r->lineHeight = (int)(SCREEN_H / r->prepWallDist);
	r->drawStart = -r->lineHeight / 2 + SCREEN_H / 2;
	if (r->drawStart < 0) 
		r->drawStart = 0;
	r->drawEnd = r->lineHeight / 2 + SCREEN_H / 2;
	if (r->drawEnd >= SCREEN_H) 
		r->drawEnd = SCREEN_H - 1;
}

void choose_tex(t_render *r, t_game *g)
{
	// 8) choose texture id based on map value (clamped)
	r->texId = worldMap[r->mapY][r->mapX] - 1;
	if (r->texId < 0) 
		r->texId = 0;
	if (r->texId >= TEX_COUNT) 
		r->texId = TEX_COUNT - 1;

	// 9) calculate exact hit position on the wall (0.0..1.0)
	double wallX;
	if (r->side == 0)
		wallX = g->posY + r->prepWallDist * r->rayDirY;
	else
		wallX = g->posX + r->prepWallDist * r->rayDirX;
	wallX -= floor(wallX);

	// 10) texture X coordinate
	r->texX = (int)(wallX * (double)TEX_W);
	if (r->side == 0 && r->rayDirX > 0) 
		r->texX = TEX_W - r->texX - 1;
	if (r->side == 1 && r->rayDirY < 0) 
		r->texX = TEX_W - r->texX - 1;
	if (r->texX < 0) 
		r->texX = 0; 
	if (r->texX >= TEX_W) 
		r->texX = TEX_W - 1;
}


void draw_textured_column(t_render *r, t_game *g, int x)
{
	t_tex t;
	int y;

	t.step = 1.0 * (double)TEX_H / (double)r->lineHeight;
	t.texPos = (r->drawStart - SCREEN_H / 2 + r->lineHeight / 2) * t.step;
	y = r->drawStart;
	while (y <= r->drawEnd)
	{
		t.texY = (int)t.texPos & (TEX_H - 1);
		t.texPos += t.step;
		t.color = tex_pixel(&g->tex[r->texId], r->texX, t.texY);
		t.shade = 1.0 / (1.0 + r->prepWallDist * 0.08);
		if (t.shade < 0.25) t.shade = 0.25;
		t.r = (unsigned int)(((t.color >> 16) & 0xFF) * t.shade);
		t.gg = (unsigned int)(((t.color >> 8) & 0xFF) * t.shade);
		t.b = (unsigned int)((t.color & 0xFF) * t.shade);
		t.shaded = (t.r << 16) | (t.gg << 8) | t.b;
		pixel_put(&g->screen, x, y, t.shaded);
		y++;
	}
}

void render(t_game *g)
{
    draw_background(g);
	t_render r;
	int x;

	x = 0;
    while (x < SCREEN_W)
    {
        r.cameraX = 2.0 * x / (double)SCREEN_W - 1.0;
        r.rayDirX = g->dirX + g->planeX * r.cameraX;
        r.rayDirY = g->dirY + g->planeY * r.cameraX;
        r.deltaDistX = (r.rayDirX == 0) ? 1e30 : fabs(1.0 / r.rayDirX);
        r.deltaDistY = (r.rayDirY == 0) ? 1e30 : fabs(1.0 / r.rayDirY);
		r.mapX = (int)g->posX;
		r.mapY = (int)g->posY;
		count_delta(&r, g);
		dda(&r);
		compute_perp_wall_dist(&r);
		choose_tex(&r, g);
		draw_textured_column(&r, g, x);
		x++;
    }
    mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);
}

void compute_next_position(t_game *g, double *nx, double *ny)
{
    if (g->move_w)
    {
        *nx = g->posX + g->dirX * MOVE_SPEED;
        *ny = g->posY + g->dirY * MOVE_SPEED;
    }
    if (g->move_s)
    {
        *nx = g->posX - g->dirX * MOVE_SPEED;
        *ny = g->posY - g->dirY * MOVE_SPEED;
    }
    if (g->move_a)
    {
        *nx = g->posX - g->dirY * MOVE_SPEED;
        *ny = g->posY + g->dirX * MOVE_SPEED;
    }
    if (g->move_d)
    {
        *nx = g->posX + g->dirY * MOVE_SPEED;
        *ny = g->posY - g->dirX * MOVE_SPEED;
    }
}

void update_player(t_game *g)
{
	double nx;
	double ny;
	double rot;
	double oldDirX;
	double oldPlaneX;

	compute_next_position(g, &nx, &ny);
	if ((int)g->posY >= 0 && (int)g->posY < MAP_H && (int)nx >= 0 && (int)nx < MAP_W)
		if (worldMap[(int)g->posY][(int)nx] == 0) g->posX = nx;
	if ((int)ny >= 0 && (int)ny < MAP_H && (int)g->posX >= 0 && (int)g->posX < MAP_W)
		if (worldMap[(int)ny][(int)g->posX] == 0) g->posY = ny;
    if (g->rot_l || g->rot_r)
    {
        rot = g->rot_l ? ROT_SPEED : -ROT_SPEED;
        oldDirX = g->dirX;
        g->dirX = g->dirX * cos(rot) - g->dirY * sin(rot);
        g->dirY = oldDirX * sin(rot) + g->dirY * cos(rot);
        oldPlaneX = g->planeX;
        g->planeX = g->planeX * cos(rot) - g->planeY * sin(rot);
        g->planeY = oldPlaneX * sin(rot) + g->planeY * cos(rot);
    }
}

int key_press(int keycode, void *param)
{
    t_game *g = (t_game *)param;
    if (keycode == KEY_ESC) { mlx_destroy_window(g->mlx, g->win); exit(0); }
    if (keycode == KEY_W) g->move_w = 1;
    if (keycode == KEY_S) g->move_s = 1;
    if (keycode == KEY_A) g->move_a = 1;
    if (keycode == KEY_D) g->move_d = 1;
    if (keycode == KEY_LEFT)  g->rot_l = 1;
    if (keycode == KEY_RIGHT) g->rot_r = 1;
    return 0;
}

int key_release(int keycode, void *param)
{
    t_game *g = (t_game *)param;
    if (keycode == KEY_W) g->move_w = 0;
    if (keycode == KEY_S) g->move_s = 0;
    if (keycode == KEY_A) g->move_a = 0;
    if (keycode == KEY_D) g->move_d = 0;
    if (keycode == KEY_LEFT)  g->rot_l = 0;
    if (keycode == KEY_RIGHT) g->rot_r = 0;
    return 0;
}

int loop_hook(void *param)
{
    t_game *g = (t_game *)param;
    update_player(g);
    render(g);
    return 0;
}

void load_textures(t_game *g)
{
    int w = TEX_W;
    int h = TEX_H;
    const char *files[TEX_COUNT] = {
        "./assets/redbrick.xpm",
        "./assets/greystone.xpm",
        "./assets/bluestone.xpm",
        "./assets/eagle.xpm",
        "./assets/Wall.xpm"
    };

    for (int i = 0; i < TEX_COUNT; i++)
    {
        g->tex[i].img = mlx_xpm_file_to_image(g->mlx, (char *)files[i], &w, &h);
        if (!g->tex[i].img)
        {
            write(2, "Failed to load texture: %s\n", 13);
            exit(1);
        }
        g->tex[i].addr = mlx_get_data_addr(g->tex[i].img,
            &g->tex[i].bpp, &g->tex[i].line_len, &g->tex[i].endian);
    }
}

int main(void)
{
    t_game g;

    for (size_t i = 0; i < sizeof(g); i++) ((char *)&g)[i] = 0;

    g.mlx = mlx_init();
    if (!g.mlx) { write(2, "mlx_init failed\n", 16); return 1; }

    g.win = mlx_new_window(g.mlx, SCREEN_W, SCREEN_H, "Textured Cub3D - WASD + Arrows");
    g.screen.img = mlx_new_image(g.mlx, SCREEN_W, SCREEN_H);
    g.screen.addr = mlx_get_data_addr(g.screen.img, &g.screen.bpp, &g.screen.line_len, &g.screen.endian);

    // initial player values
    g.posX = 3.5; g.posY = 5.5;
    g.dirX = -1.0; g.dirY = 0.0;
    g.planeX = 0.0; g.planeY = 0.66;

    load_textures(&g);

    mlx_hook(g.win, 2, 1L<<0, key_press, &g);
    mlx_hook(g.win, 3, 1L<<1, key_release, &g);
    mlx_loop_hook(g.mlx, loop_hook, &g);
    mlx_loop(g.mlx);

    return 0;
}
