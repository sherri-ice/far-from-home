#ifndef MODEL_LEVEL_GENERATOR_H_
#define MODEL_LEVEL_GENERATOR_H_

class LevelGenerator {
 public:
  explicit LevelGenerator(int level = 0);
  ~LevelGenerator() = default;

  void GenerateLevel(int level);

  double GetPlayerSpeed() const;

 private:
  int current_level_;
  int max_number_of_cats_at_level_;
  double player_speed_;
  double visibility_radius_;
};

#endif  // MODEL_LEVEL_GENERATOR_H_
