#include <gtest/gtest.h>
#include "yaml-cpp/yaml.h"
#include "custom_mutator.h"
#include <cstdlib>

TEST(CustomMutator, RunSuccessfully) {
  char env[] = "SQUIRREL_CONFIG_FILE=./data/squirrel_config.yaml";
  putenv(env);

  SquirrelMutator* mutator = static_cast<SquirrelMutator*>(afl_custom_init(nullptr, 0));
  for(int i = 0; i < 100; i++) {
    afl_custom_queue_new_entry(mutator, (const unsigned char*)"./data/queries/1.sql", nullptr);
  }
  afl_custom_deinit(mutator);
}