#ifndef TOR_EVENTDNS_H
#define TOR_EVENTDNS_H

/* Error codes 0-5 are as described in RFC 1035. */
#define DNS_ERR_NONE 0
/* The name server was unable to interpret the query */
#define DNS_ERR_FORMAT 1
/* The name server was unable to process this query due to a problem with the
 * name server */
#define DNS_ERR_SERVERFAILED 2
/* The domain name does not exist */
#define DNS_ERR_NOTEXIST 3
/* The name server does not support the requested kind of query */
#define DNS_ERR_NOTIMPL 4
/* The name server refuses to reform the specified operation for policy
 * reasons */
#define DNS_ERR_REFUSED 5
/* The reply was truncated or ill-formated */
#define DNS_ERR_TRUNCATED 65
/* An unknown error occurred */
#define DNS_ERR_UNKNOWN 66
/* Communication with the server timed out */
#define DNS_ERR_TIMEOUT 67
/* The request was canceled because the DNS subsystem was shut down. */
#define DNS_ERR_SHUTDOWN 68

#define DNS_IPv4_A 1
#define DNS_PTR 2
#define DNS_IPv6_AAAA 3

#define DNS_QUERY_NO_SEARCH 1

#define DNS_OPTION_SEARCH 1
#define DNS_OPTION_NAMESERVERS 2
#define DNS_OPTION_MISC 4
#define DNS_OPTIONS_ALL 7

/*
 * The callback that contains the results from a lookup.
 * - type is either DNS_IPv4_A or DNS_IPv6_AAAA or DNS_PTR
 * - count contains the number of addresses of form type
 * - ttl is the number of seconds the resolution may be cached for.
 * - addresses needs to be cast according to type
 */
typedef void (*evdns_callback_type) (int result, char type, int count, int ttl, void *addresses, void *arg);

int evdns_init(void);
void evdns_shutdown(int fail_requests);
const char *evdns_err_to_string(int err);
int evdns_nameserver_add(uint32_t address);
int evdns_count_nameservers(void);
int evdns_clear_nameservers_and_suspend(void);
int evdns_resume(void);
int evdns_nameserver_ip_add(const char *ip_as_string);
int evdns_nameserver_sockaddr_add(const struct sockaddr *sa, socklen_t len);
void evdns_set_default_outgoing_bind_address(const struct sockaddr *addr, socklen_t addrlen);
int evdns_resolve_ipv4(const char *name, int flags, evdns_callback_type callback, void *ptr);
int evdns_resolve_ipv6(const char *name, int flags, evdns_callback_type callback, void *ptr);
struct in_addr;
struct in6_addr;
int evdns_resolve_reverse(const struct in_addr *in, int flags, evdns_callback_type callback, void *ptr);
int evdns_resolve_reverse_ipv6(const struct in6_addr *in, int flags, evdns_callback_type callback, void *ptr);
int evdns_set_option(const char *option, const char *val, int flags);
int evdns_resolv_conf_parse(int flags, const char *);
#ifdef _WIN32
int evdns_config_windows_nameservers(void);
#endif
void evdns_search_clear(void);
void evdns_search_add(const char *domain);
void evdns_search_ndots_set(const int ndots);

typedef void (*evdns_debug_log_fn_type)(int is_warning, const char *msg);
void evdns_set_log_fn(evdns_debug_log_fn_type fn);

void evdns_set_transaction_id_fn(uint16_t (*fn)(void));
void evdns_set_random_bytes_fn(void (*fn)(char *, size_t));

#define DNS_NO_SEARCH 1

/* Structures and functions used to implement a DNS server. */

struct evdns_server_request {
	int flags;
	int nquestions;
	struct evdns_server_question **questions;
};
struct evdns_server_question {
	int type;
	int dns_question_class;
	char name[1];
};
typedef void (*evdns_request_callback_fn_type)(struct evdns_server_request *, void *);
#define EVDNS_ANSWER_SECTION 0
#define EVDNS_AUTHORITY_SECTION 1
#define EVDNS_ADDITIONAL_SECTION 2

#define EVDNS_TYPE_A	   1
#define EVDNS_TYPE_NS	   2
#define EVDNS_TYPE_CNAME   5
#define EVDNS_TYPE_SOA	   6
#define EVDNS_TYPE_PTR	  12
#define EVDNS_TYPE_MX	  15
#define EVDNS_TYPE_TXT	  16
#define EVDNS_TYPE_AAAA	  28

#define EVDNS_QTYPE_AXFR 252
#define EVDNS_QTYPE_ALL	 255

#define EVDNS_CLASS_INET   1

struct evdns_server_port *evdns_add_server_port(tor_socket_t socket, int is_tcp, evdns_request_callback_fn_type callback, void *user_data);
void evdns_close_server_port(struct evdns_server_port *port);

int evdns_server_request_add_reply(struct evdns_server_request *req, int section, const char *name, int type, int class, int ttl, int datalen, int is_name, const char *data);
int evdns_server_request_add_a_reply(struct evdns_server_request *req, const char *name, int n, const void *addrs, int ttl);
int evdns_server_request_add_aaaa_reply(struct evdns_server_request *req, const char *name, int n, const void *addrs, int ttl);
int evdns_server_request_add_ptr_reply(struct evdns_server_request *req, struct in_addr *in, const char *inaddr_name, const char *hostname, int ttl);
int evdns_server_request_add_cname_reply(struct evdns_server_request *req, const char *name, const char *cname, int ttl);

struct sockaddr;
int evdns_server_request_get_requesting_addr(struct evdns_server_request *req, struct sockaddr *sa, int addr_len);

int evdns_server_request_respond(struct evdns_server_request *req, int err);
int evdns_server_request_drop(struct evdns_server_request *req);

#endif	// !EVENTDNS_H
