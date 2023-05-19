/******************************************************************************/
/*                                                                            */
/*                       Les meilleurs films selon TMDB                       */
/*                          Auteur:  CyberCookieKing                          */
/*                                                                            */
/* Objectif :                                                                 */
/*  Récupérer des informations sur les meilleurs films selon TMDB             */
/*                                                                            */
/* Installation :                                                             */
/*  - Installez les packages de développement de libcurl et libjson-c         */
/*  - Obtenez une clé API à partir de The Movie Database                      */
/*                                                                            */
/* Compilation :                                                              */
/*  gcc -o tmdb tmdb.c -lcurl -ljson-c                                        */
/*                                                                            */
/* Utilisation :                                                              */
/*  - Exécutez le programme 'tmdb'                                            */
/*  - Le programme affichera les informations sur les 10 meilleurs films      */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>
#include <curl/curl.h>

#define API_KEY "VOTRE_CLEF_API"
#define URL_TOP_RATED "https://api.themoviedb.org/3/movie/top_rated"

// Structure pour stocker les informations d'un film
struct Movie {
    char title[256];
    char poster[256];
    char summary[1024];
};

// Fonction de rappel pour traiter la réponse de la requête CURL
size_t write_callback(void *contents, size_t size, size_t nmemb, char *output) {
    strcat(output, (char *)contents);
    return size * nmemb;
}

int main() {
    CURL *curl;
    CURLcode res;
    char output[16384] = ""; // Stocke la réponse de la requête
    output[0] = '\0'; // Initialisation de la chaîne de caractères
    struct json_object *json_obj, *results, *movie, *title, *poster, *summary;
    struct Movie movies[10]; // Stocke les informations des 10 meilleurs films

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        char url[256];
        sprintf(url,"%s?language=fr-FR&page=1&api_key=%s", URL_TOP_RATED, API_KEY);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, output);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "Erreur lors de la requête : %s\n", curl_easy_strerror(res));
            return 1;
        }

        curl_easy_cleanup(curl);
    } else {
        fprintf(stderr, "Impossible d'initialiser CURL.\n");
        return 1;
    }

    // Analyse de la réponse JSON
    json_obj = json_tokener_parse(output);
    json_object_object_get_ex(json_obj, "results", &results);

    int i;
    int num_movies = json_object_array_length(results);
    for (i = 0; i < num_movies && i < 10; i++) {
        movie = json_object_array_get_idx(results, i);
        json_object_object_get_ex(movie, "title", &title);
        json_object_object_get_ex(movie, "poster_path", &poster);
        json_object_object_get_ex(movie, "overview", &summary);

        strcpy(movies[i].title, json_object_get_string(title));
        sprintf(movies[i].poster, "https://image.tmdb.org/t/p/w200%s", json_object_get_string(poster));
        strcpy(movies[i].summary, json_object_get_string(summary));
    }

    // Affichage des informations des films
    for (i = 0; i < num_movies && i < 10; i++) {
        printf("Film %d:\n", i + 1);
        printf("Titre: %s\n", movies[i].title);
        printf("Affiche: %s\n", movies[i].poster);
        printf("Résumé: %s\n", movies[i].summary);
        printf("\n");
    }

    json_object_put(json_obj);
    curl_global_cleanup();

    return 0;
}
