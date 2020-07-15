/**
 * - This file makes rerquest to the swapi.dev and takes JSON file. 
 *   Uses libcurl – the multiprotocol file transfer library. 
 *
 * - More about libcurl: https://curl.haxx.se/libcurl/ .
 *
 */

#include "takejson.h"
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

/**
 * struct memory - Is used for saving requested information.
 * @response: Saves information like a response from request.
 *
 * This structure save json text from swapi.dev for future using. 
 */
struct memory {
	char *response;
};

/**
 * cb() - Callback function.
 * @data: Pointer to the delivered data
 * @size: Is always 1.
 * @nmemb: Size of that data, number of memory bites.
 * @userdata: pointer to the data structure.
 *
 * This callback function cb() gets called by libcurl as soon as there is data 
 * received that needs to be saved.
 * 
 * Context: For most transfers, this callback gets called many times and each 
 *          invoke delivers another chunk of data. The data passed to this 
 *          function will not be null-terminated!
 * Return:  The number of bytes actually taken care of. 
 *
 * If that amount differs from the amount passed to your callback function, 
 * it'll signal an error condition to the library.
 */
size_t cb(char *data, size_t size, size_t nmemb, void *userdata)
{
	size_t realsize = size * nmemb;
	struct memory *mem = (struct memory *)userdata;
	char *ptr = malloc(realsize + 1);
	if(ptr == NULL) {
		fprintf(stderr, "Error: out of memory\n");		
		return 0;
	}
		
	mem->response = ptr;
	memcpy(&(mem->response[0]), data, realsize);
	mem->response[realsize] = 0;
	
	return realsize;
}

/**
 * take_json() - Takes json file from request.
 * @link: String which has API's link to the json file.
 *
 * This function take_json() uses function from libcurl - The libcurl API. Takes 
 * API's link and using curl functions get json information from this link.
 * 
 * Context: If information transfer has not been this function shows Error. And  
 *          returns empty buffer.
 * Return:  Buffer which contains json file.
 */
char *take_json(char *link)
{			
	struct memory chunk;
	char *inf;
	CURL *curl = curl_easy_init();	
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, link);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
		CURLcode res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			fprintf(stderr, "Error: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	} 
	inf = (char *)malloc(strlen(chunk.response));
	inf = (char *)chunk.response;
	return inf;
}
