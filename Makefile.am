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
          src/config/parse.hh \
          src/config/parse.hxx \
          src/config/parse.cc

MISC = \
       src/misc/addrinfo/addrinfo-error.cc \
       src/misc/addrinfo/addrinfo-error.hh \
       src/misc/addrinfo/addrinfo-iterator.hh \
       src/misc/addrinfo/addrinfo.cc \
       src/misc/addrinfo/addrinfo.hh \
       src/misc/fd.cc \
       src/misc/fd.hh \
       src/misc/json.hh \
       src/misc/socket.hh \
       src/misc/sys-wrapper.hh \
       src/misc/unistd.hh \
       src/misc/logger.cc \
       src/misc/logger.hh \
       src/misc/buffer.cc

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
          src/events/send.cc

LEGISLATOR = \
           src/legislator/legislator.cc \
           src/legislator/legislator-factory.cc

SOCKET = \
         src/socket/default-socket.cc \
         src/socket/default-socket.hh \
         src/connection/connection.cc \
         src/socket/socket.hh 

SOURCES = \
          $(CONFIG) \
          $(EVENTS) \
          $(LEGISLATOR) \
          $(MISC) \
          $(SOCKET) \
          $(SCHEDULER) \
          $(NULL)


# Compile source files again to avoid silenting undefined references.
paxos_SOURCES = \
                 $(SOURCES) \
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
