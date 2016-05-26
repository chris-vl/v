DIST_SUBDIRS = secp256k1 univalue

AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS) $(HARDENED_LDFLAGS)
AM_CXXFLAGS = $(HARDENED_CXXFLAGS)
AM_CPPFLAGS = $(HARDENED_CPPFLAGS)

if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) $(AM_CPPFLAGS) $(CPPFLAGS) -D__STDC_LIMIT_MACROS"
endif

VCOIN_CONFIG_INCLUDES=-I$(builddir)/config
VCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

VCOIN_INCLUDES += -I$(srcdir)/secp256k1/include
VCOIN_INCLUDES += -I$(srcdir)/univalue/include

LIBVCOIN_SERVER=libvcoin_server.a
LIBVCOIN_WALLET=libvcoin_wallet.a
LIBVCOIN_COMMON=libvcoin_common.a
LIBVCOIN_CLI=libvcoin_cli.a
LIBVCOIN_UTIL=libvcoin_util.a
LIBVCOIN_CRYPTO=crypto/libvcoin_crypto.a
LIBVCOINQT=qt/libvcoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la
LIBUNIVALUE=univalue/libunivalue.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)
  
$(LIBUNIVALUE): $(wildcard univalue/lib/*) $(wildcard univalue/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libvcoin_crypto.a \
  libvcoin_util.a \
  libvcoin_common.a \
  libvcoin_server.a \
  libvcoin_cli.a
if ENABLE_WALLET
VCOIN_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libvcoin_wallet.a
endif
if ENABLE_ZMQ
EXTRA_LIBRARIES += libvcoin_zmq.a
endif

if BUILD_VCOIN_LIBS
lib_LTLIBRARIES = libvcoinconsensus.la
LIBVCOIN_CONSENSUS=libvcoinconsensus.la
else
LIBVCOIN_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =
BENCHMARKS =

if BUILD_VCOIND
  bin_PROGRAMS += vcoind
endif

if BUILD_VCOIN_UTILS
  bin_PROGRAMS += vcoin-cli vcoin-tx
endif

.PHONY: FORCE check-symbols check-security
# vcoin core #
VCOIN_CORE_H = \
  addrman.h \
  alert.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/merkle.h \
  consensus/params.h \
  consensus/validation.h \
  core_io.h \
  core_memusage.h \
  hash.h \
  httprpc.h \
  httpserver.h \
  init.h \
  key.h \
  keystore.h \
  dbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  policy/rbf.h \
  pow.h \
  prevector.h \
  primitives/block.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  reverselock.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  scheduler.h \
  script/interpreter.h \
  script/script.h \
  script/script_error.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  torcontrol.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  versionbits.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  wallet/walletdb.h \
  zmq/zmqabstractnotifier.h \
  zmq/zmqconfig.h\
  zmq/zmqnotificationinterface.h \
  zmq/zmqpublishnotifier.h


obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libvcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between vcoind and vcoin-qt
libvcoin_server_a_CPPFLAGS = $(AM_CPPFLAGS) $(VCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS) $(EVENT_CFLAGS) $(EVENT_PTHREADS_CFLAGS)
libvcoin_server_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libvcoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  httprpc.cpp \
  httpserver.cpp \
  init.cpp \
  dbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  torcontrol.cpp \
  txdb.cpp \
  txmempool.cpp \
  validationinterface.cpp \
  versionbits.cpp \
  $(VCOIN_CORE_H)

if ENABLE_ZMQ
LIBVCOIN_ZMQ=libvcoin_zmq.a

libvcoin_zmq_a_CPPFLAGS = $(VCOIN_INCLUDES) $(ZMQ_CFLAGS)
libvcoin_zmq_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libvcoin_zmq_a_SOURCES = \
  zmq/zmqabstractnotifier.cpp \
  zmq/zmqnotificationinterface.cpp \
  zmq/zmqpublishnotifier.cpp
endif


# wallet: shared between vcoind and vcoin-qt, but only linked
# when wallet enabled
libvcoin_wallet_a_CPPFLAGS = $(AM_CPPFLAGS) $(VCOIN_INCLUDES)
libvcoin_wallet_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libvcoin_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  policy/rbf.cpp \
  $(VCOIN_CORE_H)

# crypto primitives library
crypto_libvcoin_crypto_a_CPPFLAGS = $(AM_CPPFLAGS) $(VCOIN_CONFIG_INCLUDES)
crypto_libvcoin_crypto_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
crypto_libvcoin_crypto_a_SOURCES = \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# common: shared between vcoind, and vcoin-qt and non-server tools
libvcoin_common_a_CPPFLAGS = $(AM_CPPFLAGS) $(VCOIN_INCLUDES)
libvcoin_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libvcoin_common_a_SOURCES = \
  amount.cpp \
  arith_uint256.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  consensus/merkle.cpp \
  core_read.cpp \
  core_write.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  primitives/block.cpp \
  primitives/transaction.cpp \
  protocol.cpp \
  pubkey.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(VCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libvcoin_util_a_CPPFLAGS = $(AM_CPPFLAGS) $(VCOIN_INCLUDES)
libvcoin_util_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libvcoin_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(VCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libvcoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between vcoin-cli and vcoin-qt
libvcoin_cli_a_CPPFLAGS = $(AM_CPPFLAGS) $(VCOIN_INCLUDES)
libvcoin_cli_a_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
libvcoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(VCOIN_CORE_H)

nodist_libvcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# vcoind binary #
vcoind_SOURCES = vcoind.cpp
vcoind_CPPFLAGS = $(AM_CPPFLAGS) $(VCOIN_INCLUDES)
vcoind_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
vcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
vcoind_SOURCES += vcoind-res.rc
endif

vcoind_LDADD = \
  $(LIBVCOIN_SERVER) \
  $(LIBVCOIN_COMMON) \
  $(LIBUNIVALUE) \
  $(LIBVCOIN_UTIL) \
  $(LIBVCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_ZMQ
vcoind_LDADD += $(LIBVCOIN_ZMQ) $(ZMQ_LIBS)
endif

if ENABLE_WALLET
vcoind_LDADD += libvcoin_wallet.a
endif

vcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS) $(EVENT_PTHREADS_LIBS) $(EVENT_LIBS)

# vcoin-cli binary #
vcoin_cli_SOURCES = vcoin-cli.cpp
vcoin_cli_CPPFLAGS = $(AM_CPPFLAGS) $(VCOIN_INCLUDES) $(EVENT_CFLAGS)
vcoin_cli_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
vcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
vcoin_cli_SOURCES += vcoin-cli-res.rc
endif

vcoin_cli_LDADD = \
  $(LIBVCOIN_CLI) \
  $(LIBUNIVALUE) \
  $(LIBVCOIN_UTIL)

vcoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(EVENT_LIBS)
#

# vcoin-tx binary #
vcoin_tx_SOURCES = vcoin-tx.cpp
vcoin_tx_CPPFLAGS = $(AM_CPPFLAGS) $(VCOIN_INCLUDES)
vcoin_tx_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)
vcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
vcoin_tx_SOURCES += vcoin-tx-res.rc
endif

vcoin_tx_LDADD = \
  $(LIBUNIVALUE) \
  $(LIBVCOIN_COMMON) \
  $(LIBVCOIN_UTIL) \
  $(LIBVCOIN_CRYPTO) \
  $(LIBSECP256K1)

vcoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# vcoinconsensus library #
if BUILD_VCOIN_LIBS
include_HEADERS = script/vcoinconsensus.h
libvcoinconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/vcoinconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libvcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libvcoinconsensus_la_LDFLAGS = $(AM_LDFLAGS) -no-undefined $(RELDFLAGS)
libvcoinconsensus_la_LIBADD = $(LIBSECP256K1)
libvcoinconsensus_la_CPPFLAGS = $(AM_CPPFLAGS) -I$(builddir)/obj -I$(srcdir)/secp256k1/include -DBUILD_VCOIN_INTERNAL
libvcoinconsensus_la_CXXFLAGS = $(AM_CXXFLAGS) $(PIE_FLAGS)

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a
CLEANFILES += *.gcda *.gcno
CLEANFILES += compat/*.gcda compat/*.gcno
CLEANFILES += consensus/*.gcda consensus/*.gcno
CLEANFILES += crypto/*.gcda crypto/*.gcno
CLEANFILES += policy/*.gcda policy/*.gcno
CLEANFILES += primitives/*.gcda primitives/*.gcno
CLEANFILES += script/*.gcda script/*.gcno
CLEANFILES += support/*.gcda support/*.gcno
CLEANFILES += univalue/*.gcda univalue/*.gcno
CLEANFILES += wallet/*.gcda wallet/*.gcno
CLEANFILES += wallet/test/*.gcda wallet/test/*.gcno
CLEANFILES += zmq/*.gcda zmq/*.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	-$(MAKE) -C univalue clean
	-rm -f leveldb/*/*.gcda leveldb/*/*.gcno leveldb/helpers/memenv/*.gcda leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(AM_CXXFLAGS) $(PIE_FLAGS) $(CXXFLAGS) -c -o $@ $<

check-symbols: $(bin_PROGRAMS)
if GLIBC_BACK_COMPAT
	@echo "Checking glibc back compat..."
	$(AM_V_at) READELF=$(READELF) CPPFILT=$(CPPFILT) $(top_srcdir)/contrib/devtools/symbol-check.py < $(bin_PROGRAMS)
endif

check-security: $(bin_PROGRAMS)
if HARDEN
	@echo "Checking binary security..."
	$(AM_V_at) READELF=$(READELF) OBJDUMP=$(OBJDUMP) $(top_srcdir)/contrib/devtools/security-check.py < $(bin_PROGRAMS)
endif

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_BENCH
include Makefile.bench.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
