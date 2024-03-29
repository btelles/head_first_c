#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "spaceship.h"

bool done;
ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* timer;
ALLEGRO_DISPLAY* display;
Spaceship spaceship;

void abort_game(const char* message)
{
	printf("%s \n", message);
	exit(1);
}

void init(void)
{
	if (!al_init())
		abort_game("failed to initialize allegro!");

	if (!al_install_keyboard())
		abort_game("Couldn't find or connect the keyboard.");

	timer = al_create_timer(1.0 / 60);
	if (!timer)
		abort_game("Weird...I couldn't find or create a system timer.");

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	display = al_create_display(640, 480);
	if(!display)
		abort_game("failed to create the display!");

	event_queue = al_create_event_queue();
	if (!event_queue)
		abort_game("Weird...I couldn't create an event queue.");

	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_display_event_source(display));

    spaceship.color = al_map_rgb(0,100,0);
    spaceship.heading = 0.0f;
    spaceship.x = 320.0f;
    spaceship.y = 240.0f;

	done = false;
}
void get_user_input(int keycode)
{
	if(keycode == ALLEGRO_KEY_UP || keycode == ALLEGRO_KEY_FULLSTOP)
	    spaceship.y -= 1;
}
void update_graphics(void)
{
	draw_spaceship(&spaceship);
}

void shutdown(void)
{
	if (timer)
		al_destroy_timer(timer);

	if (display)
		al_destroy_display(display);

	if (event_queue)
		al_destroy_event_queue(event_queue);

}

void game_loop(void)
{
	bool redraw = true;
	al_start_timer(timer);
	int frame = 0;

	while (!done) {
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);

		if (event.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;
			//update_logic();
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
			if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
				done = true;
			}
			get_user_input(event.keyboard.keycode);
		}
		if (redraw && al_is_event_queue_empty(event_queue)) {
			redraw = false;
			al_clear_to_color(al_map_rgb(0,0,0));
			update_graphics();
			al_flip_display();
		}
		frame++;
	}
}


int main(int argc, char **argv) {

	init();
	game_loop();
	shutdown();
	return 0;
}
