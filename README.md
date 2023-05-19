# TMDB Top Rated Movies

Ce programme récupère les informations The Movie Database (TMDB) sur les meilleurs films et les affiche à l'utilisateur.

## Prérequis

Avant d'exécuter ce programme, assurez-vous d'avoir les éléments suivants :

- Les bibliothèques libcurl et libjson-c.
  
  ```bash
  apt install libcurl4-openssl-dev libjson-c-dev
  ```
  
- Une clé API TMDB valide. Vous pouvez obtenir une clé API en vous inscrivant sur le site [TMDB](https://www.themoviedatabase.org) et en créant une application.

## Personnalisation de la clé API

Assurez-vous de remplacer la valeur de la constante `API_KEY` dans le fichier `tmdb.c` par votre propre clé API TMDB.

```c
#define API_KEY "VOTRE_CLÉ_API"
```

## Compilation

Pour compiler le programme, exécutez la commande suivante :

```bash
gcc -o tmdb tmdb.c -lcurl -ljson-c
```

## Utilisation

Pour exécuter le programme, utilisez la commande suivante :

```bash
./tmdb
```

Le programme récupérera les informations sur les 10 meilleurs films selon TMDB et les affichera à l'écran.
Pour chaque film, les informations affichées sont les suivantes :

- Titre du film
- Affiche du film
- Résumé du film
