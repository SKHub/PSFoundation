//
// Reachability.h
// PSFoundation
//
//  Includes code by the following:
//   - Apple Inc.         2010.  Apple Sample.
//   - Andrew Donoho.     2009.  BSD.
//   - Matthias Tretter.  2011.
//

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>
#include <netinet/in.h>

typedef enum {
	NotReachable = 0,
	ReachableViaWiFi,
	ReachableViaWWAN
} NetworkStatus;

extern NSString* const kReachabilityChangedNotification;

@interface Reachability : NSObject {
    SCNetworkReachabilityRef reachabilityRef;
}

//reachabilityWithHostName- Use to check the reachability of a particular host name. 
+ (Reachability *)reachabilityWithHostName:(NSString *)hostName;

//reachabilityWithAddress- Use to check the reachability of a particular IP address. 
+ (Reachability *)reachabilityWithAddress:(const struct sockaddr_in*)hostAddress;

//reachabilityForInternetConnection- checks whether the default route is available.  
//  Should be used by applications that do not connect to a particular host
+ (Reachability *)reachabilityForInternetConnection;

//reachabilityForLocalWiFi- checks whether a local wifi connection is available.
+ (Reachability *)reachabilityForLocalWiFi;

//Start listening for reachability notifications on the current run loop
- (BOOL)startNotifier;
- (void) stopNotifier;

// These are the status tests.
@property (nonatomic, readonly, getter=currentReachabilityStatus) NetworkStatus status;

//WWAN may be available, but not active until a connection has been established.
//WiFi may require a connection for VPN on Demand.
@property (nonatomic, readonly, getter=isConnectionRequired) BOOL connectionRequired;
- (BOOL) connectionRequired DEPRECATED_ATTRIBUTE;

// The main direct test of reachability.
@property (nonatomic, readonly, getter=isReachable) BOOL reachable;

// Dynamic, on demand connection?
@property (nonatomic, readonly, getter=isConnectionOnDemand) BOOL connectionOnDemand;

// Is user intervention required?
@property (nonatomic, readonly, getter=isInterventionRequired) BOOL interventionRequired;

// Routines for specific connection testing by your app.
@property (nonatomic, readonly, getter=isReachableViaWWAN) BOOL reachableViaWWAN;
@property (nonatomic, readonly, getter=isReachableViaWiFi) BOOL reachableViaWiFi;

@property (nonatomic, readonly, getter=reachabilityFlags) SCNetworkReachabilityFlags flags;

@end