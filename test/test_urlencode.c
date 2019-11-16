#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Temp file, testing out codes posted on stackoverflow. */

char rfc3986[256] = {0};
char html5[256] = {0};

void url_encoder_rfc_tables_init(){

    int i;

    for (i = 0; i < 256; i++){

        rfc3986[i] = isalnum( i) || i == '~' || i == '-' || i == '.' || i == '_' ? i : 0;
        html5[i] = isalnum( i) || i == '*' || i == '-' || i == '.' || i == '_' ? i : (i == ' ') ? '+' : 0;
    }
}

char *url_encode( char *table, const unsigned char *s, char *enc){

    for (; *s; s++){

        if (table[*s]) sprintf( enc, "%c", table[*s]);
        else sprintf( enc, "%%%02X", *s);
        while (*++enc);
    }

    return( enc);
}

void print_tbls(){
	url_encoder_rfc_tables_init();
	
	printf("char rfc3986[256] = {\n");
	int i, j;
	for(i = 0; i < 16; ++i){
		printf("\t");
		for(j = 0; j < 16; ++j){
			printf("%3c, ", rfc3986[i*16 + j]);
		}
		printf("\n");
	}
	printf("};\n\n\n");
	
	printf("char html5[256] = {\n");
	for(i = 0; i < 16; ++i){
		printf("\t");
		for(j = 0; j < 16; ++j){
			printf("%3c, ", html5[i*16 + j]);
		}
		printf("\n");
	}
	printf("};\n");
}


int UrlEncode(char* url, char* encode,  char* buffer, unsigned int size)
{
	char chars[127] = {0};
	unsigned int length = 0;

	if(!url || !encode || !buffer) return 0;

   /* Create an array to hold ascii chars, loop through encode string
    * and assign to place in array. I used this construct instead of a 
	 * large if statement for speed. 
	 */
	while(*encode) chars[(int) (*encode++)] = *encode;

	/* Loop through url, if we find an encode char, replace with % and
	 * add hex as ascii chars. Move buffer up by 2 and track the length
	 * needed. If we reach the query string (?), move to query string
	 * encoding 
	 */
	
	while(size && (*buffer = *url)) {
		if(*url == '?') goto URLENCODE_QUERY_STRING;
		if(chars[*url] && size > 2) {
			*buffer++ = '%';
			sprintf(buffer, "%hhx", *url);
/*			itoa(*url, buffer, 16); */
			buffer++; size-=2; length+=2;
		}
		url++, buffer++, size--; length++;  
	}
	goto URLENCODE_RETURN;

	/* Same as above but on spaces (' '), replace with plus ('+') and
	 * convert to hex ascii. I moved this out into a separate loop for
	 * speed.
	 */
	URLENCODE_QUERY_STRING:
	while(size && (*buffer = *url)) {
		if(chars[*url] && size > 2) {
			*buffer++ = '%';
/*			if(*url == ' ') itoa('+', buffer, 16); */
			if(*url == ' ') sprintf(buffer, "%hhx", '+');
/*			else itoa(*url, buffer, 16);           */
			else sprintf(buffer, "%hhx", *url);
			buffer++; size-=2; length+=2;
		}
		url++, buffer++, size--; length++;
	}

	/* Terminate the end of the buffer, and if the buffer wasn't large
	 * enough calc the rest of the url length and return
	 */
	URLENCODE_RETURN:
	*buffer = '\0';
	if(*url) while(*url) { if(chars[*url]) length+=2; url++; length++; }
	return length;
}


int main(int argc, char** argv){
	
	const char* sRaw = "http://test.place.com/area/51?doggy=kite&units=μs";
	
	char sOut[256] = {'\0'};
	
	url_encoder_rfc_tables_init();
	
	url_encode(html5, (const unsigned char*)sRaw, sOut);
	
	printf("Encoding: %s -> %s\n", sRaw, sOut);
	
	return 0;
}
