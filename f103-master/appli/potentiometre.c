

#include "potentiometre.h"

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdint.h>

#define N_SAMPLES 10 // nombre de mesures utilisées pour la moyenne

int16_t samples[N_SAMPLES]; // tableau des N_SAMPLES dernières mesures
int i = 0; // index du tableau circulaire de mesures
int32_t sum = 0; // somme des N_SAMPLES dernières mesures

int16_t smooth_potentiometer(int16_t new_sample) {

	static int16_t is_first_iteration = 1;

	if(is_first_iteration) {
		// Si c'est la première itération et que le tableau est vide, remplir le tableau avec la première valeur
		if(samples[0] == 0) {
			for(int i = 0; i < N_SAMPLES; i++) {
				samples[i] = new_sample;
			}
		}
		is_first_iteration = 0;
		return new_sample;
	}

//    // Vérifier si la nouvelle mesure est aberrante
//    int16_t lower_limit = INT16_MAX;
//    int16_t upper_limit = INT16_MIN;
//    for (int i = 0; i < N_SAMPLES; i++) {
//        if (samples[i] < lower_limit) {
//            lower_limit = samples[i];
//        }
//        if (samples[i] > upper_limit) {
//            upper_limit = samples[i];
//        }
//    }
//    int16_t range = upper_limit - lower_limit;
//    int16_t deviation = abs(new_sample - (sum / N_SAMPLES));
//    if (deviation > range / 4) {
//        // La nouvelle mesure est aberrante, retourner la moyenne sans prendre en compte cette mesure
//        return sum / (int32_t)(N_SAMPLES - 1);
//    }
//
    // Retirer la valeur la plus ancienne de la somme des mesures
    sum -= samples[i];
    
    // Ajouter la nouvelle valeur à la somme des mesures
    sum += new_sample;
    
    // Stocker la nouvelle mesure dans le tableau circulaire
    samples[i] = new_sample;
    
    // Trier le tableau circulaire de mesures
    int16_t sorted_samples[N_SAMPLES];
    memcpy(sorted_samples, samples, N_SAMPLES * sizeof(int16_t));
    for (int i = 0; i < N_SAMPLES - 1; i++) {
        for (int j = i + 1; j < N_SAMPLES; j++) {
            if (sorted_samples[i] > sorted_samples[j]) {
                int16_t temp = sorted_samples[i];
                sorted_samples[i] = sorted_samples[j];
                sorted_samples[j] = temp;
            }
        }
    }
    
    // La nouvelle mesure est cohérente, retourner la moyenne
    i = (i + 1) % N_SAMPLES;
    return sum / (int32_t)N_SAMPLES;
}
