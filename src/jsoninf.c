/**
 * - JsonInf can reads information from JSON file and show the string from object 
 *   in this file. Uses libjson-c-dev – JSON-C implements a reference counting 
 *   object model that allows you to easily construct JSON objects in C, output 
 *   them as JSON formatted strings and parse JSON formatted strings back into the 
 *   C representation of JSON objects.
 *
 * - We takes information about api from https://swapi.dev/documentation . 
 *   From this site we take jason file.
 *
 */
#include "takejson.h"
#include "jsoninf.h"
#include <stdio.h>
#include <string.h>
#include <json-c/json.h>

/**
 * conc() - Makes concatenation.
 * @s1: The first string.
 * @s2: The second string.
 * 
 * This function makes concatenation of two strings and adds in the end "/".
 *  
 * Context: Concatenates link string and parameter string.
 * Return:  String which contains new link.
 */
char *conc(char *s1, char *s2)
{
	size_t len1 = strlen(s1);
	size_t len2 = strlen(s2);

	char *res = malloc(len1 + len2 + 1);

	strcpy(res, s1);
	strcat(res, s2);
	strcat(res, "/");	
	
	return res;
}

/**
 * set_count() - Set count of objects from swapi.dev.
 * @name: The name of resource which count is needed.
 * 
 * This function set count of objects from resource which locats in swapi.dev.
 *  
 * Context: If object not found shows Error and return 0.
 * Return:  count of object.
 */
int set_count(char *name)
{
	int count;		
		
	if(strcmp(name, "people") == 0) {
		count = 82;
	}else if(strcmp(name, "planets") == 0) {
		count = 60;
	}else if(strcmp(name, "species") == 0) {
		count = 37;
	}else if(strcmp(name, "vehicles") == 0) {
		count = 39;
	}else if(strcmp(name, "starships") == 0) {
		count = 36;
	}else {
		fprintf(stderr, "Error: Not found\n");
		return 0;
	}
	
	return count;
}

/**
 * get_atr() - Get information from json attribute.
 * @atr_name: The name of attribute from which information is taken.
 * @buf: The buffer of json file from which attribute is taken. 
 *
 * This function uses buffer of json file and takes from them attribute 
 * information. The attribute has string information. 
 *  
 * Context: If json file doesn't have attribute this function shows Error and 
 *          return string "none".
 * Return:  String of attribute information.
 */
char *get_atr(char *atr_name, char *buf)
{
	char *str;	
	int res;

	struct json_object *obj;
	struct json_object *atr;
	
	obj = json_tokener_parse(buf);
	
	res = json_object_object_get_ex(obj, atr_name, &atr);
	if (!res){
		fprintf(stderr, "No object\n");
		return "none";
	}
	str = (char *)malloc(strlen(json_object_get_string(atr)));
	str = (char *)json_object_get_string(atr);	
	
	return str;
}

/**
 * get_search_link() - Makes search link.
 * @link: From this link makes search link.
 * @name: The name of thing which is searched. 
 *
 * This function creates a search link. Uses the base link, the string 
 * "?search=" and the name.
 * 
 * Return:  String of the search link.
 */	
char *get_search_link(char *link, char *name)
{
	char *search_link;

	search_link = malloc(strlen(link) + strlen(name) + strlen("?search="));
	strcpy(search_link, link);
	strcat(search_link, "?search=");
	strcat(search_link, name);
	
	return search_link;
}

/**
 * search_name() - Gets information about found name.
 * @atr_name: The name of attribute from which information is taken.
 * @buf: The buffer of json file from which attribute is taken. 
 *
 * This function uses buffer of json file and takes from them attribute 
 * information. The attribute has string information. The buffer took 
 * information from search reference. A result of searching has array of found 
 * objects. This function take string of the object and take information from 
 * this string about attribute.  
 *  
 * Context: If json file doesn't have attribute or has not found objects after 
 *          searching this function shows Error and return string "none".
 * Return: String of attribute information.
 */
char *search_name(char *atr_name, char *buf)
{
	char *str; 
	int res;
	
	struct json_object *obj;
	struct json_object *results;
	struct json_object *result;
	struct json_object *atr;
	struct json_object *count;
	
	obj = json_tokener_parse(buf);
	res = json_object_object_get_ex(obj, "count", &count);
	if (!res){
		fprintf(stderr, "No object\n");
		return "none";
	}
	if(!json_object_get_int(count)) {
		fprintf(stderr, "No object\n");
		return "none";
	}
	
	
	res = json_object_object_get_ex(obj, "results", &results);
	if (!res){
		fprintf(stderr, "No object\n");
		return "none";
	}
	
	result = json_object_array_get_idx(results, 0);
	str = (char *)malloc(strlen(json_object_get_string(result)));
	str = (char *)json_object_get_string(result);
	obj = json_tokener_parse(str);
	res = json_object_object_get_ex(obj, atr_name, &atr);
	if (!res){
		fprintf(stderr, "No object\n");
		return "none";
	}
	str = (char *)malloc(strlen(json_object_get_string(atr)));
	str = (char *)json_object_get_string(atr);

	return str;
}

void get_list_of_name(char link[], char par[])
{
	char *api_link = conc(link, par);	
	char *buf;
	int count = set_count(par);
		for (int i = 0; i < count; i++) {
			char p[11];		
			sprintf(p, "%d", i+1);		
			char* count_link = conc(api_link, p);
			buf = take_json(count_link);
			printf("%s %s #%d: %s\n", par, "name", i+1, get_atr("name", buf));
			free(count_link);
			free(buf);
		}
}
