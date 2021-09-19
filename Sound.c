#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <SDL2/SDL_audio.h>
#include <math.h>
#include "lists.h"
#define PI2 6.28318530718

list notelist;

double wavOut (list note)
{
	double wavval = 0;
	for (int i = 0; i <= note.used; i++){
		if (note.notes[i].ty == 'q')
			wavval += (sin(note.notes[i].time)>0? 1: -1)/note.used;
		else if (note.notes[i].ty == 'w')
			wavval += (((note.notes[i].time/PI2/2)-floor((note.notes[i].time/PI2/2)+.5))-1)/note.used;
		else if (note.notes[i].ty == 't')
			wavval += ((4 * fabs((note.notes[i].time/PI2)-floor((note.notes[i].time/PI2)+.5)))-1)/note.used;
		else
			wavval += sin(note.notes[i].time)/note.used;
	}
	return wavval;
}

void callback(void* userdata, Uint8* stream, int len) {
	short * snd = (short*)(stream);
	len /= sizeof(*snd);
	for(int i = 0; i < len; i++) //Fill array with frequencies, mathy-math stuff
	{
		snd[i] = wavOut(notelist) * 12000;
		//wave types
		//sin wave
		//printf("%f\n", sin(time));

		//square wave
		//printf("%d\n", sin(time)>0? 1: -1);

		//sawblade
		//printf("%f\n", (4 * (time/PI2/2)-floor((time/PI2/2)+.5))-1);

		//triangle
		//printf("%f\n", (4 * fabs((time/PI2)-floor((time/PI2)+.5)))-1);

		for (int i = 0; i <= notelist.used; i++){
			notelist.notes[i].time += notelist.notes[i].freq * PI2 / 48000.0;
			if(notelist.notes[i].time >= PI2)
				notelist.notes[i].time -= PI2;
		}
	}
}

int main(int arcgc, char **argv[]) {
	listInit (&notelist, 3);
	SDL_Init(SDL_INIT_AUDIO);

	notes prototype;
	prototype.time = 0;
	prototype.freq = 440;
	prototype.ty = 's';
	

	SDL_AudioSpec spec, aspec; // the specs of our piece of "music"
	SDL_zero(spec);
	spec.freq = 48000; //declare specs
	spec.format = AUDIO_S16SYS;
	spec.channels = 1;
	spec.samples = 4096;
	spec.userdata = NULL;
	spec.callback = callback;


	//Open audio, if error, print
	SDL_AudioDeviceID dev;
	dev = SDL_OpenAudioDevice(NULL, 0, &spec, &aspec, SDL_AUDIO_ALLOW_FORMAT_CHANGE);

	/* Start playing, "unpause" */
	SDL_PauseAudioDevice(dev, 0);

	while(true) //Stall for time while audio plays
	{
		addNote(&notelist, prototype);
		notelist.notes[0].freq = 440;
		SDL_Delay (3000);
		addNote(&notelist, prototype);
		notelist.notes[1].freq = 586.6667;
		notelist.notes[1].ty = 't';
		SDL_Delay (3000);
		addNote(&notelist, prototype);
		notelist.notes[1].freq = 660;
		SDL_Delay (3000);
		removeNote(&notelist);
		removeNote(&notelist);
		removeNote(&notelist);
		addNote(&notelist, prototype);
		addNote(&notelist, prototype);
		notelist.notes[0].freq = 440;
		notelist.notes[1].freq = 586.6667;
		SDL_Delay (3000);
		removeNote(&notelist);
		removeNote(&notelist);
	}
	SDL_CloseAudio();
}