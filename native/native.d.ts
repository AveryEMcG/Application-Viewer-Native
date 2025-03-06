
////

// Application Scanner

declare interface ScannedApplication {
  windowTitle: string;
  procedurePath: string;
  procedureName: string;
}

declare type ScannedApplications = Array<ScannedApplication>;
declare type ApplicationScannerCallback = (sa: ScannedApplications) => void;

declare interface NativeApplicationScannerModule {
  ListenForApplications: (callback: ApplicationScannerCallback) => void;
  StopListener: () => void;
}


// Application Status

declare interface ApplicationStatus {
  status: 'open' | 'hidden' | 'closed';
  dimensions?: { x, y, width, height };
}

declare type ApplicationStatusCallback = (as:ApplicationStatus)=>void;

declare interface NativeApplicationStatusModule {
  ListenForStatus: (callback: ApplicationStatusCallback) => void;
  StopListener: () => void;
}

////
// Native Modules

declare type NativeModuleMap = {
  "native-application-scanner": NativeApplicationScannerModule,
};

declare type NativeModuleTypes = keyof NativeModuleMap;
