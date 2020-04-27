#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

int main(int argc, char *argv[]) {

   //printf ("Inicializando o SDL e o SDL_mixer\n");
   if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
      fprintf(stderr, "Nao foi possivel inicializar o SDL: %s", SDL_GetError());
      return 1;
   }

   int audio_rate = 44100;
   /* 22050 é o ideal para a frequência na maioria dos jogos. Se o seu objetivo for criar algum GuitarHero, talvez seja melhor aumentar esse valor. A qualidade de CD é 44100. */

   Uint16 audio_format = AUDIO_S16SYS; /* Ajuste de amostras com 16 bits. Pode ser necessário alterar para 8 bits: AUDIO_S8 */
   int audio_channels = 2; /* 1-Mono; 2-Stereo */
   int audio_buffers = 4096; /* Buffer para armazenamento de trechos do audio*/

   /* Mix_OpenAudio inicializa o sistema de audio de acordo com as configurações estabelecidas acima */
   if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
      fprintf(stderr, "Nao foi possivel inicializar o audio: %s\n", Mix_GetError());
      exit(1);
   }

   /* Ponteiro que receberá a amostra de audio do arquivo WAV e armazenará essa amostra na memória */
   Mix_Chunk *sound = NULL;

   sound = Mix_LoadWAV("sound.wav"); /* Carrega a música a partir do arquivo WAV) */
   if (sound == NULL) {
      fprintf(stderr, "Impossível carregar arquivo WAV: %s\n", Mix_GetError());
   }

   /* Abrir janela em 320x240 */
   SDL_Surface *screen;
   screen = SDL_SetVideoMode(320, 240, 0, SDL_ANYFORMAT);
   if (screen == NULL) {
      fprintf(stderr, "Impossível configurar modo de vídeo: s\n", SDL_GetError());
      return 1;
   }

   int channel;
   channel = Mix_PlayChannel(-1, sound, 0);
   if (channel == -1) {
      fprintf(stderr, "Impossível reproduzir arquivo WAV: %s\n", Mix_GetError());
   }

   /* Aguarda o fim da reprodução e finaliza o programa liberando antes os recursos alocados. */
   while (Mix_Playing(channel) != 0);

   Mix_FreeChunk(sound);

   Mix_CloseAudio();

   SDL_Quit();
}

