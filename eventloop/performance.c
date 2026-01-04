#include <stdint.h>
#include <string.h>
#include <assert.h>


#include "performance.h"


#define MODULE_PERFORMANCE_ARRAY_SIZE 5

typedef struct MODULE_PERFORMANCE {
    uint32_t total_time;
    uint32_t total_runs;
    uint32_t average_run_time;
} module_performance;



// variables

static uint32_t controls_size = 0;
static uint32_t modules_size  = 0;

static module_performance modules[MODULE_PERFORMANCE_ARRAY_SIZE];

static uint32_t event_queue_misses        = 0;
static uint32_t event_queue_depth_total   = 0;
static uint32_t event_queue_depth_runs    = 0;
static uint32_t event_queue_depth_average = 0;
static uint32_t current_module            = 0;

void performance_set_controls_size(uint32_t max) {
    controls_size = max;
}
void performance_set_module_size(uint32_t max) {
    modules_size = max;
}

void performance_init() {
    event_queue_misses        = 0;
    event_queue_depth_total   = 0;
    event_queue_depth_runs    = 0;
    event_queue_depth_average = 0;

    memset(modules, 0, sizeof(module_performance));

    // protections
    if (modules_size > MODULE_PERFORMANCE_ARRAY_SIZE) {
        assert("Module Size must not exceed performance monitor array size.");
    }

}