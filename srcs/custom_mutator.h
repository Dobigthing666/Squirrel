#ifndef __CUSTOM_MUTATOR_H__
#define __CUSTOM_MUTATOR_H__

#include "afl-fuzz.h"
#include "config_validate.h"
#include "db.h"


struct SquirrelMutator {
  SquirrelMutator(DataBase *db) : database(db) {}
  ~SquirrelMutator() { delete database; }
  DataBase *database;
  std::string current_input;
};

extern "C" {
void *afl_custom_init(afl_state_t *afl, unsigned int seed);
void afl_custom_deinit(SquirrelMutator *data);
u8 afl_custom_queue_new_entry(SquirrelMutator *mutator,
                              const unsigned char *filename_new_queue,
                              const unsigned char *filename_orig_queue);
unsigned int afl_custom_fuzz_count(SquirrelMutator *mutator,
                                   const unsigned char *buf, size_t buf_size);
size_t afl_custom_fuzz(SquirrelMutator *mutator, uint8_t *buf, size_t buf_size, u8 **out_buf, uint8_t *add_buf, size_t add_buf_size,  // add_buf can be NULL
                       size_t max_size);
}

#endif // __CUSTOM_MUTATOR_H__