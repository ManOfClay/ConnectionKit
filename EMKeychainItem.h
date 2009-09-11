/*Copyright (c) 2009 Extendmac, LLC. <support@extendmac.com>
 
 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:
 
 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.
 */

//Version 1.0, Last Updated September 11th, 2009.


#import <Cocoa/Cocoa.h>
#import <Carbon/Carbon.h>
#import <Security/Security.h>

@interface EMKeychainItem : NSObject 
{
	@private
	NSString *mUsername;
	NSString *mPassword;
	NSString *mLabel;
	
	@protected
	SecKeychainItemRef mCoreKeychainItem;
}

/*!
 @abstract Returns whether or not errors are logged.
 @discussion Errors occur whenever a keychain item fails to appropriately update a property, or when a given keychain item cannot be found.
 */
+ (BOOL)logsErrors;

//! @abstracts Sets whether or not errors are logged.
+ (void)setLogsErrors:(BOOL)logsErrors;

//! @abstracts Locks the keychain.
+ (void)lockKeychain;

//! @abstract Unlocks the keychain.
+ (void)unlockKeychain;

//! @abstract The keychain item's username.
@property (readwrite, copy) NSString *username;

//! @abstract The keychain item's password.
@property (readwrite, copy) NSString *password;

//! @abstract The keychain item's label.
@property (readwrite, copy) NSString *label;

/*!
	@abstract Removes the receiver from the keychain.
	@discussion After calling this method, you should generally discard of the receiver. The receiver cannot be "re-added" to the keychain; invoke either addGenericKeychainItemForServer:... or addInternetKeychainItemForServer:... instead.
 */
- (void)removeFromKeychain;

@end 

#pragma mark -

@interface EMGenericKeychainItem : EMKeychainItem
{
	@private
	NSString *mServiceName;
}

//! @abstract The keychain item's service name.
@property (readwrite, copy) NSString *serviceName;

/*!
	@abstract Returns, if possible, a generic keychain item that corresponds to the given service.
	@param serverName The service name.
	@param username The username.
	@result An EMGenericKeychainItem if the keychain item can be discovered. Otherwise, nil.
 */
+ (EMGenericKeychainItem *)genericKeychainItemForService:(NSString *)serviceName
											withUsername:(NSString *)username;

/*!
	@abstract Adds a keychain item for the given service.
	@param serivceName The service name.
	@param username The username.
	@param password The password to associate with the username and service.
	@result An EMGenericKeychainItem if the service can be added to the keychain. Otherwise, nil.
 */
+ (EMGenericKeychainItem *)addGenericKeychainItemForService:(NSString *)serviceName
											   withUsername:(NSString *)username
												   password:(NSString *)password;
@end

#pragma mark -

@interface EMInternetKeychainItem : EMKeychainItem
{
	@private
	NSString *mServer;
	NSString *mPath;
	NSInteger mPort;
	SecProtocolType mProtocol;
}


/*!
	@abstract Returns, if possible, an internet keychain item that corresponds to the given server.
	@param server The server.
	@param username The username.
	@param path The path.
	@param port The port.
	@parma protocol The protocol.
	@result An EMInternetKeychainItem if the keychain item can be discovered. Otherwise, nil.
 */
+ (EMInternetKeychainItem *)internetKeychainItemForServer:(NSString *)serverString
											 withUsername:(NSString *)usernameString
													 path:(NSString *)pathString
													 port:(NSInteger)port
												 protocol:(SecProtocolType)protocol;

/*!
	@abstract Adds a keychain item for the given server.
	@param server The server.
	@param username The username.
	@param password The password to associate with the server, username, path, port, and protocol.
	@param path The path.
	@param port The port.
	@param protocol The protocol.
	@result An EMInternetKeychainItem if the item can be added to the keychain. Otherwise, nil.
 */
+ (EMInternetKeychainItem *)addInternetKeychainItemForServer:(NSString *)serverString
												withUsername:(NSString *)usernameString
													password:(NSString *)passwordString
														path:(NSString *)pathString
														port:(NSInteger)port
													protocol:(SecProtocolType)protocol;

//! @abstract The keychain item's server.
@property (readwrite, copy) NSString *server;

//! @abstract The keychain item's path.
@property (readwrite, copy) NSString *path;

//! @abstract The keychain item's port.
@property (readwrite, assign) NSInteger port;

//! @abstract The keychain item's protocol.
@property (readwrite, assign) SecProtocolType protocol;

@end