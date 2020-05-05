NULL =
EXTRA_DIST = autogen.sh
ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

AM_MAKEFLAGS = --no-print-directory

AM_CPPFLAGS = \
              -include $(top_builddir)/config.h \
              -I${top_srcdir}/src \
              -I${top_srcdir}/lib

AM_CXXFLAGS = \
              $(WARN_CXXFLAGS) \
              $(BOOST_CPPFLAGS) \
              -Werror=unused-parameter \
              -Werror=missing-field-initializers \
              -Werror=overloaded-virtual \
              -Wno-inline \
              $(NULL)

AM_LDFLAGS = \
             $(WARN_LDFLAGS) \
             $(BOOST_LDFLAGS) \
             -lev \
             -lssl \
             -lcrypto \
             -lstdc++fs \
             $(NULL)

AM_LDFLAGS += \
              -Wno-unused-command-line-argument \
              $(NULL)

bin_PROGRAMS = paxos


CONFIG = \
          src/config/config.hh \
          src/config/config.cc \
          src/config/proxy.hh \
          src/config/proxy.cc \
          src/config/parse.hh \
          src/config/parse.hxx \
          src/config/parse.cc \
          src/config/timeout.hh \
          src/config/timeout.cc \
          src/config/upstream.hh \
          src/config/upstream.cc

VHOST = \
          src/vhost/vhost-factory.cc \
          src/vhost/vhost-static-file.cc \
          src/vhost/vhost-reverse-proxy.cc \
          src/vhost/connection.hh \
          src/vhost/connection.cc \
          src/vhost/apm.hh \
          src/vhost/apm.cc \
          src/vhost/vhost.cc

MISC = \
       src/misc/buffer.hh \
       src/misc/buffer.cc \
       src/misc/option.hh \
       src/misc/option.cc \
       src/misc/addrinfo/addrinfo-error.cc \
       src/misc/addrinfo/addrinfo-error.hh \
       src/misc/addrinfo/addrinfo-iterator.hh \
       src/misc/addrinfo/addrinfo.cc \
       src/misc/addrinfo/addrinfo.hh \
       src/misc/fd.cc \
       src/misc/fd.hh \
       src/misc/json.hh \
       src/misc/openssl/base64.cc \
       src/misc/openssl/base64.hh \
       src/misc/openssl/ssl-error.cc \
       src/misc/openssl/ssl-error.hh \
       src/misc/openssl/ssl-wrapper.hh \
       src/misc/openssl/ssl.hh \
       src/misc/socket.hh \
       src/misc/sys-wrapper.hh \
       src/misc/unistd.hh \
       src/misc/readiness/readiness.cc \
       src/misc/readiness/readiness.hh \
       src/misc/logger.cc \
       src/misc/logger.hh

EVENTS = \
          src/events/event-loop.hh \
          src/events/event-loop.cc \
          src/events/events.cc \
          src/events/events.hh \
          src/events/listener.hh \
          src/events/listener.cc \
          src/events/register.hh \
          src/events/register.cc \
          src/events/register.hxx \
          src/events/receive.hh \
          src/events/receive.cc \
          src/events/send.hh \
          src/events/send.cc \
          src/events/send-file.hh \
          src/events/send-file.cc \
          src/events/send-request.hh \
          src/events/send-request.cc \
          src/events/receive-response.hh \
          src/events/receive-response.cc \
          src/events/file-sender.hh \
          src/events/file-sender.cc \
          src/events/reverse-proxy.cc \
          src/events/reverse-proxy.hh

ERROR = \
        src/error/init-error.hh \
        src/error/not-implemented.hh \
        src/error/parsing-error.hh \
        src/error/connection-closed.hh \
        src/error/connection-failed.hh \
        src/error/backend-unavailable.hh

SOCKET = \
         src/socket/default-socket.cc \
         src/socket/default-socket.hh \
         src/socket/socket.hh \
         src/socket/ssl-socket.cc \
         src/socket/ssl-socket.hh

TIMER = \
        src/timer/timer.cc \
        src/timer/timer.hh \
        src/timer/queue.cc \
        src/timer/queue.hh \
        src/timer/throughput-queue.cc \
        src/timer/throughput-queue.hh \
        src/timer/proxy-queue.cc \
        src/timer/procy-queue.hh \
        src/timer/queue-manager.cc \
        src/timer/queue-manager.hh

SCHEDULER = \
        src/scheduler/scheduler.cc \
        src/scheduler/scheduler.hh \
        src/scheduler/round-robin.cc \
        src/scheduler/round-robin.hh \
        src/scheduler/failover.cc \
        src/scheduler/failover.hh \
        src/scheduler/fail-robin.cc \
        src/scheduler/fail-robin.hh \
        src/scheduler/send-health.cc \
        src/scheduler/send-health.hh \
        src/scheduler/recv-health.cc \
        src/scheduler/recv-health.hh

SOURCES = \
          src/request/error.cc \
          src/request/error.hh \
          src/request/request.cc \
          src/request/request.hh \
          src/request/message.hh \
          src/request/message.cc \
          src/request/response.hh \
          src/request/response.cc \
          src/request/types.hh \
          src/vhost/dispatcher.cc \
          src/vhost/dispatcher.hh \
          src/vhost/vhost-factory.hh \
          src/vhost/vhost-reverse-proxy.hh \
          src/vhost/vhost-static-file.hh \
          src/vhost/vhost.hh \
          $(CONFIG) \
          $(VHOST) \
          $(MISC) \
          $(EVENTS) \
          $(ERROR) \
          $(SOCKET) \
          $(TIMER) \
          $(SCHEDULER) \
          $(NULL)


# Compile source files again to avoid silenting undefined references.
paxos_SOURCES = \
                 src/main.cc \
                 $(NULL)

# https://www.gnu.org/software/automake/manual/html_node/Objects-created-both-with-libtool-and-without.html
paxos_CXXFLAGS = $(AM_CXXFLAGS)


#Unit tests
if USING_CRITERION

# Criterion rules.


#test_queue: tests/test_queue/test_queue.cc src/misc/queue.hh src/misc/queue.hxx
#	$(CXX) $(AM_CPPFLAGS) -o $@ tests/test_queue/test_queue.cc -lcriterion

#test_%: tests/test_%/test_%.cc 
#	$(CXX) -o $@ $^ -lcriterion

unit: $(TESTS_UNIT) $(SOURCES)
	for t in $(TESTS_UNIT); do \
		./$$t ; \
	done;

tap: $(TESTS_UNIT) $(SOURCES)
	for t in $(TESTS_UNIT); do \
		./$$t --tap; \
	done;
endif

#debug_queue: tests/test_queue/debug_queue.cc src/misc/queue.hh src/misc/queue.hxx
#	$(CXX) $(AM_CPPFLAGS) -o $@ tests/test_queue/debug_queue.cc -g
