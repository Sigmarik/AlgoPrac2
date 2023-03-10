#define OUTPUT_FILE "measurements.log"
#define OUTPUT_TABLE "measurements.csv"

static const size_t MAX_ARRAY_LENGTH = 1e7 + 100;

static const unsigned PROGRESS_BAR_LENGTH = 30;

static const unsigned DEBUG_BATCH_SIZE = 5;

static const long long THRESHOLD_TIME = 3e6;  // If the single test takes longer then 3 seconds, it will terminate.
