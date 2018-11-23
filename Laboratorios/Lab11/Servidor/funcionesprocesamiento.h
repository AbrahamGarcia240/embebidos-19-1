#ifndef funcionesprocesamiento_H
#define funcionesprocesamiento_H


void GrayToRGB (unsigned char *imagenRGB, unsigned char *imagenGray, uint32_t width, uint32_t iniBloque, uint32_t finBloque );
void brilloImagen(unsigned char *imagenGray, uint32_t width, uint32_t height);
unsigned char * reservarMemoria(uint32_t width, uint32_t height);
void filtroPB(unsigned char *imagenO, unsigned char *imagenP, uint32_t width, uint32_t iniBloque, uint32_t finBloque );

unsigned char * RGBToGray( unsigned char *imagenRGB, uint32_t width, uint32_t iniBloque, uint32_t finBloque );



#endif
