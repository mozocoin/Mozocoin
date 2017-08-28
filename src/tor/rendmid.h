#ifndef TOR_RENDMID_H
#define TOR_RENDMID_H

int rend_mid_establish_intro(or_circuit_t *circ, const uint8_t *request,
                             size_t request_len);
int rend_mid_introduce(or_circuit_t *circ, const uint8_t *request,
                       size_t request_len);
int rend_mid_establish_rendezvous(or_circuit_t *circ, const uint8_t *request,
                                  size_t request_len);
int rend_mid_rendezvous(or_circuit_t *circ, const uint8_t *request,
                        size_t request_len);

#endif

