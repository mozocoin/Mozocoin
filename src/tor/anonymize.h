#ifndef TOR_ANONYMIZE_H
#define TOR_ANONYMIZE_H

#ifdef __cplusplus
extern "C" {
#endif

    char const* anonymize_tor_data_directory(
    );

    char const* anonymize_service_directory(
    );

    int check_interrupted(
    );

    void set_initialized(
    );

    void wait_initialized(
    );

#ifdef __cplusplus
}
#endif

#endif

