#include <random> 

// Serie di Tools per la generazione rapida di numeri random 
namespace randomTools {

  float randomFloat(float start = 0, float stop = 1) {
    // Generatore random di float tra start e stop di default genera tra 0 e 1
    std::random_device rd; 
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(start, stop); 
    return distr(eng); 
  } 

  int randomInt(int start = 0, int stop = 0) {
    // Generatore random di interi tra start e stop. 
    std::random_device rd; 
    std::default_random_engine eng(rd()); 
    std::uniform_int_distribution<int> distr(start, stop); 
    return distr(eng); 
  }
} 
