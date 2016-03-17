#############
#Author:venu<venu.chkuri@yahoo.com>
#
#
#


include $(TOPDIR)/rules.mk

PKG_NAME:=skfhomekit-bridge
PKG_VERSION:=2016-3-17
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=git://nbd.name/uhttpd.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=e57bf6d8bfa465a50eea2c30269acdfe751a46fd
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz
PKG_MAINTAINER:=Jo-Philipp Wich <jow@openwrt.org>




#TARGET_LDFLAGS+=/usr/include/openssl
#PKG_BUILD_DEPENDS:=libopenssl
PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)



include $(INCLUDE_DIR)/package.mk



define Package/PersonalHomekit

	SECTION:=utils

	CATEGORY:=Utilities
	        
	#DEPENDS:=+ibpthread +lssl +lcrypto +ldl +ldns_sd

	TITLE:=Helloworld -- prints a snarky message

endef


define Build/Prepare

	mkdir -p $(PKG_BUILD_DIR)

	$(CP) ./src/* $(PKG_BUILD_DIR)/

endef


#define Build/Compile
#	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)
#endef

#define Build/Compile

#	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS)

#endef



define Package/PersonalHomekit/install

	$(INSTALL_DIR) $(1)/bin

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/PHK $(1)/bin/

endef



$(eval $(call BuildPackage,PersonalHomekit))
#$(eval $(call BuildPackage,PersonalHomekit,+ibpthread +lssl +lcrypto +ldl +ldns_sd))


