#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct bmpfile_header {
	uint32_t filesz;
	uint16_t creator1;
	uint16_t creator2;
	uint32_t bmp_offset;
} FILEH;
typedef struct {
	uint32_t header_sz;
	int32_t width;
	int32_t height;
	uint16_t nplanes;
	uint16_t bitspp;
	uint32_t compress_type;
	uint32_t bmp_bytesz;
	int32_t hres;
	int32_t vres;
	uint32_t ncolors;
	uint32_t nimpcolors;
} INFOH;

int main(int argc , char * argv[]){
	INFOH ih ;
	FILEH fh ;
	FILE* pic ;
	FILE* output ;
	char* o_str ;
	int i ,j , color, counts, color_tmp;
	pic = fopen(argv[1], "r") ;
	fseek(pic, 0x2, SEEK_SET);
	fread(&fh.filesz, 4, 1, pic);
	fprintf(stderr,"fh.filesz:0x%X\n",fh.filesz);
	fseek(pic, 0xa, SEEK_SET);
	fread(&fh.bmp_offset, 4, 1, pic) ;
	fprintf(stderr,"fh.bmp_offset:0x%X\n",fh.bmp_offset);
	fseek(pic, 0x1c, SEEK_SET);
	fread(&ih.bitspp, 2, 1, pic);
	fprintf(stderr,"ih.bitspp:0x%X\n",ih.bitspp);
	fseek(pic, 0x12, SEEK_SET);
	fread(&ih.width, 4, 1, pic);
	fprintf(stderr,"ih.width:%d\n",ih.width);
	fseek(pic, 0x16, SEEK_SET);
	fread(&ih.height, 4, 1, pic);
	fprintf(stderr,"ih.height:%d\n",ih.height);
	fseek(pic, 0x1e, SEEK_SET);
	fread(&ih.compress_type, 4, 1, pic);
	fprintf(stderr,"ih.compresstype:0x%X\n",ih.compress_type);
	o_str = malloc(strlen(argv[1] + 5));
	strcpy(o_str, argv[1]);
	strcat(o_str, ".rle");
	output = fopen(o_str, "w");
	free(o_str);


	fseek(pic, fh.bmp_offset ,SEEK_SET);
	for(i = 1 ; i < ih.height + 1; i++){
//		fprintf(output, "%d:", i);
		counts = 0 ;
		for(j = 1 ; j < ih.width + 1; j ++){
			fread(&color,1,1,pic);
			if(color == color_tmp ){
				counts ++ ;
				if(j == ih.width ){
					fprintf(output, "(%d,%d)", color, counts);
				}
			}else{
				if(counts){
					fprintf(output, "(%d,%d)",color_tmp, counts);
				}
				counts = 1 ;
			}
			color_tmp = color ;
		}
		putc('\n', output);
	}
}
