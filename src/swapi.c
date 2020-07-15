/**
 * - This program creates GUI for swapi.dev using gtk+ 3.
 *   Shows information about people, planets, species, vehicles, starships from 
 *   The Star Wars API. Can search object and show the list of objects. 
 *   
 * - Information about gtk+ 3 can be found 
 *   hear https://developer.gnome.org/gtk3/stable/ .
 *
 */
#include "takejson.h"
#include "jsoninf.h"
#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>

GtkWidget *text_widget;
GtkTextBuffer *buffer;
GtkWidget *lable_num;
GtkWidget *search;

/**
 * unit: String of resource. Depends on button callback functions.
 */
static char *unit = "people";
/**
 * search_text: String of search. Information is taken from search editor.
 */
static char *search_text = "none";
/**
 * unit: Array of resource's number.
 */
static int num[] = {1, 1, 1, 1, 1, 1};

/**
 * output_text() - Displays text.
 * @atr_arr: array of atributes which this function shows.
 * @len: len of atr_arr.
 * @index: number of resource.
 * 
 * This function displays information about attributes which was taken from JSON
 * file about resource. Information pass to the text widget.
 *  
 * Context: When information about atribute wasn't found, this function wright 
 *          in widget "none".
 */
static void output_text(char **atr_arr, int len, int index)
{
	char p[3];	
	char *json_buf;
	char *search_link;
	char *link;
	char label_str[10];	

	link = "https://swapi.dev/api/";
	sprintf(p, "%d", num[index]);
	sprintf(label_str, "%d/%d", num[index], set_count(unit));
	gtk_label_set_text(GTK_LABEL(lable_num), label_str);
	search_link = conc(link, unit);
	search_link = conc(search_link, p);
	json_buf = take_json(search_link);
	buffer = gtk_text_buffer_new(NULL);
	for (int i = 0; i < len; i++)
	{	
		char text[100];		
		char *atr_info = get_atr(atr_arr[i], json_buf);
		if(strcmp(atr_arr[i], "homeworld") == 0)
		{	
			char home_link[(int)strlen(atr_info)+1]; 
			int j,k;
			for (j = 0, k = 0; j < (int)strlen(atr_info)+1; k++, j++) {
				if(k == 4)		
					home_link[k++] = 's';	
				home_link[k] = atr_info[j];			
			}
			char *home_buf = take_json(home_link);
			atr_info = get_atr("name", home_buf);
			
		}
		sprintf(text, "%s: %s\n",atr_arr[i], atr_info);
		gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer),
									 text, strlen(text));
		gtk_text_view_set_buffer (GTK_TEXT_VIEW(text_widget), buffer);
	}
}

/**
 * search_fun() - Search and displays text.
 * @atr_arr: array of atributes which this function shows.
 * @len: len of atr_arr.
 *  
 * This function search and displays information about attributes which was 
 * taken from JSON file about resource. Information pass to the text widget.
 *  
 * Context: When name wasn't found this function wright in widget "Not in <resource>".
 *          When information about atribute wasn't found, this function wright 
 *          in widget "none". 
 */
static void search_fun(char **atr_arr, int len)
{
	char *link = "https://swapi.dev/api/";
	
	char *search_link = conc(link, unit);
	char *buf;

	buffer = gtk_text_buffer_new(NULL);	
	search_link = get_search_link(search_link, search_text);
	buf = take_json(search_link);
	printf("link %s\n", search_link);
	for(int i = 0; i < len; i++)
	{
		char text[100];		
		char *atr_info = search_name(atr_arr[i], buf);
		if(strcmp(atr_info, "none") == 0)
			sprintf(text, "Not in %s\n", unit);
		else
			sprintf(text, "%s: %s\n",atr_arr[i], atr_info);
		gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer),
									 text, strlen(text));
		gtk_text_view_set_buffer (GTK_TEXT_VIEW(text_widget), buffer);
	}
} 

/**
 * btn_people_cl() - Callback function about people.
 *   
 * This function callback output_text() or search_fun(), depends on search status.
 * If search_text = "none" callback output_text() else search_fun(). 
 * This fun set unit = "people".
 */
static void btn_people_cl(void) 
{		
	char *atr_arr[] = {"name", "gender", "height", "mass", "hair_color",
					   "skin_color", "eye_color", 
					   "birth_year", "created", "edited"};
	int len = sizeof(atr_arr)/sizeof(*atr_arr);	
	unit = "people";
	if(strcmp(search_text, "none") == 0)
		output_text(atr_arr, len, 0);
	else	
		search_fun(atr_arr, len);
}

/**
 * btn_people_cl() - Callback function about planets.
 *   
 * This function callback output_text() or search_fun(), depends on search status.
 * If search_text = "none" callback output_text() else search_fun().
 * This fun set unit = "planets". 
 */
static void btn_planets_cl(void) 
{
	char *atr_arr[] = {"name", "rotation_period", "orbital_period", "diameter", 
					   "climate", "gravity", "terrain", 
					   "surface_water", "population", "created", "edited"};
	int len = sizeof(atr_arr)/sizeof(*atr_arr);	
	unit = "planets";
	if(strcmp(search_text, "none") == 0)
		output_text(atr_arr, len, 1);
	else	
		search_fun(atr_arr, len);	
}

/**
 * btn_people_cl() - Callback function about species.
 *   
 * This function callback output_text() or search_fun(), depends on search status.
 * If search_text = "none" callback output_text() else search_fun().
 * This fun set unit = "species". 
 */
static void btn_species_cl(void) 
{
	char *atr_arr[] = {"name", "classification", "designation", 
					   "average_height", "skin_colors",
					   "hair_colors", "eye_colors", "average_lifespan", 
					   "created", "edited"};
	int len = sizeof(atr_arr)/sizeof(*atr_arr);		
	unit = "species";
	if(strcmp(search_text, "none") == 0)
		output_text(atr_arr, len, 2);
	else	
		search_fun(atr_arr, len);
}

/**
 * btn_people_cl() - callback function about vehicles.
 *   
 * This function callback output_text() or search_fun(), depends on search status.
 * If search_text = "none" callback output_text() else search_fun().
 * This fun set unit = "vehicles".
 */
static void btn_vehicles_cl(void) 
{
	char *atr_arr[] = {"name", "model", "manufacturer", "cost_in_credits", 
					   "length", "max_atmosphering_speed", "crew", "passengers",
					   "cargo_capacity", "consumables", "vehicle_class", 
					   "created", "edited"};
	int len = sizeof(atr_arr)/sizeof(*atr_arr);	
	unit = "vehicles";
	if(strcmp(search_text, "none") == 0)
		output_text(atr_arr, len, 3);
	else	
		search_fun(atr_arr, len);
}

/**
 * btn_people_cl() - Callback function about starships.
 *   
 * This function callback output_text() or search_fun(), depends on search status.
 * If search_text = "none" callback output_text() else search_fun().
 * This fun set unit = "starships". 
 */
static void btn_starships_cl(void) 
{
	char *atr_arr[] = {"name", "model", "manufacturer", "cost_in_credits", 
					   "length", "max_atmosphering_speed", "crew", "passengers",
					   "cargo_capacity", "consumables", "hyperdrive_rating",
					   "MGLT", "starship_class", "created", "edited"};
	int len = sizeof(atr_arr)/sizeof(*atr_arr);	
	unit = "starships";
	if(strcmp(search_text, "none") == 0)
		output_text(atr_arr, len, 4);
	else	
		search_fun(atr_arr, len);
		
}

/**
 * btn_people_cl() - Callback function, makes list of objects.
 *   
 * This function makes list of objects depends on resource. 
 */
static void btn_list_cl(void)
{
	char *link = "https://swapi.dev/api/";	
	char *api_link = conc(link, unit);	
	char *buf;
	int count = set_count(unit);
	buffer = gtk_text_buffer_new(NULL);
	gtk_text_view_set_buffer (GTK_TEXT_VIEW(text_widget), buffer);	
	
		for (int i = 0; i < count; i++) {
			char text[100];	
			char p[11];		
			sprintf(p, "%d", i+1);		
			char* count_link = conc(api_link, p);
			buf = take_json(count_link);
			sprintf(text, "%s %s #%d: %s\n", unit, "name", i+1, 
					get_atr("name", buf));
			gtk_text_buffer_insert_at_cursor(GTK_TEXT_BUFFER(buffer),
									 text, strlen(text));
			gtk_text_view_set_buffer (GTK_TEXT_VIEW(text_widget), buffer);
		}
}

/**
 * btn_search_cl() - Callback function, makes search.
 *   
 * This function callback button callback function depends on unit. 
 */
static void btn_search_cl(void)
{
	const gchar *text = gtk_entry_get_text (GTK_ENTRY(search));
	search_text = (char *)text;
	if(strcmp(unit, "people") == 0) {
		btn_people_cl();
	} else if(strcmp(unit, "planets") == 0) {
		btn_planets_cl();
	} else if(strcmp(unit, "species") == 0) {
		btn_species_cl();
	} else if(strcmp(unit, "vehicles") == 0) {
		btn_vehicles_cl();
	} else if(strcmp(unit, "starships") == 0) {
		btn_starships_cl();
	}
	search_text = "none";
}

/**
 * btn_right_cl() - Callback function, sets number of resource.
 *   
 * This function callback button callback function and increments number of unit
 * depends on unit. 
 */
static void btn_right_cl(void)
{
	if(strcmp(unit, "people") == 0) {
		num[0] = num[0] + 1;
		num[0] = num[0] == set_count(unit) + 1 ? 1: num[0];
		btn_people_cl();
	} else if(strcmp(unit, "planets") == 0) {
		num[1] = num[1] + 1;
		num[1] = num[1] == set_count(unit) + 1 ? 1: num[1];
		btn_planets_cl();
	} else if(strcmp(unit, "species") == 0) {
		num[2] = num[2] + 1;
		num[2] = num[2] == set_count(unit) + 1 ? 1: num[2];
		btn_species_cl();
	} else if(strcmp(unit, "vehicles") == 0) {
		num[3] = num[3] + 1;
		num[3] = num[3] == set_count(unit) + 1 ? 1: num[3];
		btn_vehicles_cl();
	} else if(strcmp(unit, "starships") == 0) {
		num[4] = num[4] + 1;
		num[4] = num[4] == set_count(unit) + 1 ? 1: num[4];
		btn_starships_cl();
	}
}

/**
 * btn_left_cl() - Callback function, sets number of resource.
 *   
 * This function callback button callback function and derements number of unit
 * depends on unit. 
 */
static void btn_left_cl(void)
{
	if(strcmp(unit, "people") == 0) {		
		num[0] = num[0] - 1;
		num[0] = num[0] == 0 ? set_count(unit): num[0];
		btn_people_cl();
	} else if(strcmp(unit, "planets") == 0) {
		num[1] = num[1] - 1;
		num[1] = num[1] == 0 ? set_count(unit): num[1];
		btn_planets_cl();
	} else if(strcmp(unit, "species") == 0) {
		num[2] = num[2] - 1;
		num[2] = num[2] == 0 ? set_count(unit): num[2];
		btn_species_cl();
	} else if(strcmp(unit, "vehicles") == 0) {
		num[3] = num[3] - 1;
		num[3] = num[3] == 0 ? set_count(unit): num[3];
		btn_vehicles_cl();
	} else if(strcmp(unit, "starships") == 0) {
		num[4] = num[4] - 1;
		num[4] = num[4] == 0 ? set_count(unit): num[4];
		btn_starships_cl();
	}
}

int main(int argc, char *argv[])
{
	GtkWidget *window;   
	GtkWidget *header;	
	GtkWidget *main_grid;
	GtkWidget *btn_box;
	GtkWidget *p_box;
	GtkWidget *btn_people;
	GtkWidget *btn_planets;
	GtkWidget *btn_species;
	GtkWidget *btn_vehicles;
	GtkWidget *btn_starships;
	GtkWidget *btn_left;
	GtkWidget *btn_right;
	GtkWidget *btn_search;	
	GtkWidget *btn_list;
	GtkWidget *scroll;  

	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

	main_grid = gtk_grid_new();
	
	gtk_container_add(GTK_CONTAINER(window), main_grid);

	header = gtk_header_bar_new();

	btn_box = gtk_button_box_new (GTK_ORIENTATION_HORIZONTAL);
	btn_people = gtk_button_new_with_label ("people");	
	btn_planets = gtk_button_new_with_label ("planets");
	btn_species = gtk_button_new_with_label ("species");	
	btn_vehicles = gtk_button_new_with_label ("vehicles");
	btn_starships = gtk_button_new_with_label ("starships");	
	gtk_container_add(GTK_CONTAINER(btn_box), btn_people);
	gtk_container_add(GTK_CONTAINER(btn_box), btn_planets);
	gtk_container_add(GTK_CONTAINER(btn_box), btn_species);
	gtk_container_add(GTK_CONTAINER(btn_box), btn_vehicles);
	gtk_container_add(GTK_CONTAINER(btn_box), btn_starships);
	gtk_button_box_set_layout (GTK_BUTTON_BOX(btn_box),GTK_BUTTONBOX_EXPAND);

	gtk_header_bar_pack_start (GTK_HEADER_BAR(header), btn_box);
	
	gtk_grid_attach(GTK_GRID(main_grid), header, 1, 1, 1, 1);
	
	g_signal_connect(btn_people, "clicked", G_CALLBACK(btn_people_cl), NULL);
	g_signal_connect(btn_planets, "clicked", G_CALLBACK(btn_planets_cl), NULL);
	g_signal_connect(btn_species, "clicked", G_CALLBACK(btn_species_cl), NULL);
	g_signal_connect(btn_vehicles, "clicked", 
					 G_CALLBACK(btn_vehicles_cl), NULL);
	g_signal_connect(btn_starships, "clicked",
					 G_CALLBACK(btn_starships_cl), NULL);
	scroll = gtk_scrolled_window_new(NULL, NULL);
	gtk_widget_set_size_request (GTK_WIDGET(scroll), 400, 350);
	text_widget = gtk_text_view_new();
	gtk_container_set_border_width(GTK_CONTAINER(text_widget), 10);
	gtk_widget_set_size_request (GTK_WIDGET(text_widget), 400, 350);
	gtk_container_add(GTK_CONTAINER(scroll), text_widget);
	gtk_scrolled_window_get_vscrollbar(GTK_SCROLLED_WINDOW(scroll));
	gtk_grid_attach_next_to(GTK_GRID(main_grid), scroll, header,
							GTK_POS_BOTTOM, 1, 1);
	
	btn_left = gtk_button_new_with_label("<");	
	btn_right = gtk_button_new_with_label(">");
	lable_num = gtk_label_new("/");
	btn_list = gtk_button_new_with_label("list of names");
	search = gtk_search_entry_new();
	btn_search = gtk_button_new_with_label("search");
	
	p_box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 5);
	gtk_box_pack_start (GTK_BOX(p_box), btn_left, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(p_box), lable_num, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(p_box), btn_right, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(p_box), btn_list, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(p_box), search, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(p_box), btn_search, FALSE, FALSE, 0);

	g_signal_connect(btn_left, "clicked", G_CALLBACK(btn_left_cl), NULL);
	g_signal_connect(btn_right, "clicked", G_CALLBACK(btn_right_cl), NULL);
	g_signal_connect(btn_list, "clicked", G_CALLBACK(btn_list_cl), NULL);
	g_signal_connect(btn_search, "clicked", G_CALLBACK(btn_search_cl), NULL);
	
	gtk_grid_attach_next_to(GTK_GRID(main_grid), p_box, scroll,
							GTK_POS_BOTTOM, 1, 1);

	gtk_widget_show_all(window);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	
	gtk_main();
}
