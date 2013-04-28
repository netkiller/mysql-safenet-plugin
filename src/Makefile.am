EXTRA_DIST = safenet.h
INCLUDES = -I$(top_builddir)/include $(MYSQL_INC) $(DEPS_CFLAGS) $(LIBCURL_CPPFLAGS) $(LIBCURL)

lib_LTLIBRARIES = safenet.la
mysql-udf-http_la_SOURCES = safenet.c
mysql-udf-http_la_LDFLAGS = -module
mysql-udf-http_la_LIBADD = $(DEPS_LIBS) $(LIBCURL)
