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
          src/config/config.cc \
          src/config/parse.cc

MISC = \
       src/misc/addrinfo/addrinfo-error.cc \
       src/misc/addrinfo/addrinfo.cc \
       src/misc/fd.cc \
       src/misc/logger.cc \
       src/misc/buffer.cc

MESSAGE = \
          src/message/message.cc

EVENTS = \
          src/events/event-loop.cc \
          src/events/events.cc \
          src/events/listener.cc \
          src/events/register.cc \
          src/events/receive.cc \
          src/events/send.cc

LEGISLATOR = \
           src/legislator/legislator.cc \
           src/legislator/legislator-factory.cc \
           src/legislator/ledger.cc

SOCKET = \
         src/socket/default-socket.cc \
         src/connection/connection.cc

SOURCES = \
          $(CONFIG) \
          $(EVENTS) \
          $(LEGISLATOR) \
          $(MESSAGE) \
          $(MISC) \
          $(SOCKET) \
          $(SCHEDULER) \
          $(NULL)


paxos_SOURCES = \
                 $(SOURCES) \
                 src/main.cc \
                 $(NULL)

# https://www.gnu.org/software/automake/manual/html_node/Objects-created-both-with-libtool-and-without.html
paxos_CXXFLAGS = $(AM_CXXFLAGS)


#Unit tests
if USING_CRITERION

# Criterion rules.


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
