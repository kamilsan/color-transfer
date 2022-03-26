#ifndef COLOR_L_ALPHA_BETA
#define COLOR_L_ALPHA_BETA

struct ColorLogLMS;

struct ColorLAlphaBeta {
  ColorLAlphaBeta(): l(0.0f), alpha(0.0f), beta(0.0f) {}
  ColorLAlphaBeta(float l_, float alpha_, float beta_): l(l_), alpha(alpha_), beta(beta_) {}

  ColorLogLMS toLogLMS() const;
  static ColorLAlphaBeta fromLogLMS(const ColorLogLMS& lms);

  float l;
  float alpha;
  float beta;
};

#endif // COLOR_L_ALPHA_BETA