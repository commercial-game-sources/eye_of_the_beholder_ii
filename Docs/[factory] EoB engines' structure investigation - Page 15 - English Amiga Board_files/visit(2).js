try{var dv_win = window._dv_win || window.parent._dv_win; dv_win['dvCallback_1589705816598181']($dv,window,'9c0005affca04ebfa4b3eaa2e7aa41a9','tps20238.doubleverify.com');}catch(e){try{var image=window.document.createElement('img');image.src=window.location.protocol+'//tps30.doubleverify.com/visit.jpg?ctx=818052&cmp=1619415&dvtagver=6.1.src&dvp_cbError='+encodeURIComponent(e.message)}catch(e){}}$dv.pubSub.subscribe('ImpressionServed', $uid, 'RTN_LatencyTemp', function () {try {var beforeVisitCall = '';var templateStartTime = parent.getCurrentTime();var dv_win = parent.window._dv_win;if (dv_win && dv_win.t2tTimestampData) {if (dv_win.t2tTimestampData.length >= 2) {beforeVisitCall = dv_win.t2tTimestampData[1].beforeVisitCall;}}var latency = 0;if (beforeVisitCall != '' && templateStartTime != '') {latency = templateStartTime - beforeVisitCall;}if(latency > 1000 && latency < 90000) {$dv.registerEventCall($uid, { dvp_ltncy: latency });}} catch (e) {};});$dv.pubSub.subscribe('IABViewableImpression', '9c0005affca04ebfa4b3eaa2e7aa41a9', 'RTN_IABViewableImpression', function(){ var tagServiceUrl = decodeURIComponent('https://ad.doubleclick.net/activity;src=1295336;type=cs;cat=Viewa0;u14=125994;u15=18330;u16=[DVP_ADID];ord=1|https://ad.doubleclick.net/activity;src=1295336;type=cs;cat=Viewa0;u14=%5bCMP%5d;u15=%5bSID%5d;u16=%5bDVP_ADID%5d;ord=1'); tagServiceUrl = $dv.resolveMacros(tagServiceUrl, $dv.tags['9c0005affca04ebfa4b3eaa2e7aa41a9']);  $dv.domUtilities.addImage(tagServiceUrl, $dv.tags['9c0005affca04ebfa4b3eaa2e7aa41a9'].tagElement.parentElement,1);});$dv.pubSub.subscribe('IABViewableImpression', '9c0005affca04ebfa4b3eaa2e7aa41a9', 'RTN_IABViewableImpression', function(){ var tagServiceUrl = decodeURIComponent('https://ad.doubleclick.net/ddm/activity/src=1295336;type=custom;cat=viewa2;u1=[TOTALPAGETIME];u2=[BUCKET_0];u3=[BUCKET_1_9];u4=[BUCKET_10_19];u5=[BUCKET_20_29];u6=[BUCKET_30_39];u7=[BUCKET_40_49];u8=[BUCKET_50_59];u9=[BUCKET_60_69];u10=[BUCKET_70_79];u11=[BUCKET_80_89];u12=[BUCKET_90_99];u13=[BUCKET_100];u14=125994;u15=18330;u16=[DVP_ADID];u17=;dc_lat=;dc_rdid=;tag_for_child_directed_treatment=;ord=1|https://ad.doubleclick.net/ddm/activity/src=1295336;type=custom;cat=viewa2;u1=%5bTOTALPAGETIME%5d;u2=%5bBUCKET_0%5d;u3=%5bBUCKET_1_9%5d;u4=%5bBUCKET_10_19%5d;u5=%5bBUCKET_20_29%5d;u6=%5bBUCKET_30_39%5d;u7=%5bBUCKET_40_49%5d;u8=%5bBUCKET_50_59%5d;u9=%5bBUCKET_60_69%5d;u10=%5bBUCKET_70_79%5d;u11=%5bBUCKET_80_89%5d;u12=%5bBUCKET_90_99%5d;u13=%5bBUCKET_100%5d;u14=%5bCMP%5d;u15=%5bSID%5d;u16=%5bDVP_ADID%5d;u17=;dc_lat=;dc_rdid=;tag_for_child_directed_treatment=;ord=1'); tagServiceUrl = $dv.resolveMacros(tagServiceUrl, $dv.tags['9c0005affca04ebfa4b3eaa2e7aa41a9']);  $dv.domUtilities.addImage(tagServiceUrl, $dv.tags['9c0005affca04ebfa4b3eaa2e7aa41a9'].tagElement.parentElement,1);});$dv.pubSub.subscribe('ImpressionServed', $uid, 'RTN_CollectDvtpSrcPerformanceData', function(){ try {var dvTagCreated = '';var dvTagCreatedSetInCallBack = '';var beforeVisitCall = '';var callTPSFromIframe = window.callTPSFromIframe;var beginVisitCallbackTS = '';var templateStartTime = parent.getCurrentTime();var dv_win = parent.window._dv_win;if(dv_win && dv_win.t2tTimestampData) {if (dv_win.t2tTimestampData.length >= 1) {dvTagCreated = dv_win.t2tTimestampData[0].dvTagCreated;}if (dv_win.t2tTimestampData.length >= 2) {beforeVisitCall = dv_win.t2tTimestampData[1].beforeVisitCall;}}if ($dv.tags[$uid]) {dvTagCreatedSetInCallBack = $dv.tags[$uid].t2tIframeCreationTime;beginVisitCallbackTS = $dv.tags[$uid].beginVisitCallbackTS;}var message = $dv.tags[$uid].dv_protocol + '//' + $dv.tags[$uid].ServerPublicDns + '/event.gif?impid=' + $uid;message += '&dvp_dvTagCreated='+dvTagCreated+'&dvp_dvTagCreatedSetInCallBack='+dvTagCreatedSetInCallBack+'&dvp_callTPSFromIframe='+callTPSFromIframe+'&dvp_beforeVisitCall='+beforeVisitCall+'&dvp_beginVisitCallbackTS='+beginVisitCallbackTS+'&dvp_templateStartTime='+templateStartTime+'&dvp_tpsProcessingTime=+0';var image = window.document.createElement('img');image.src = message;} catch(e) {};});$dv.pubSub.subscribe ('ImpressionServed', $uid, 'SendAdEntitiesForMA', function() {var tag = $dv.tags[$uid];var targetWin = tag.t2tIframeWindow;if(!targetWin){var t2tIframeId = tag.t2tIframeId;if(t2tIframeId){var iFrame = window.parent.getElementById(t2tIframeId);if(iFrame){targetWin = iFrame.contentWindow;}}}if(targetWin){var dateNow = 0;if(Date.now){dateNow = Date.now();} else {dateNow = +new Date();}var message = {action : 'notifyMultipleAdsAdEntityInformationReady',adEntityInformation : {comparisonItems : [{name : 'cmp', value : 18469418, bitFlag : 1, maxTimeMS : 5000, eventToFire : 'CampaignMultipleAd'},{name : 'clcd', value : 1828362, bitFlag : 2, maxTimeMS : 5000},{name : 'plmt', value : 18469431, bitFlag : 4, maxTimeMS : 5000},{name : 'mp', value : 1609, bitFlag : 8, maxTimeMS : 5000},{name : 'adv', value : 868983, bitFlag : 16, maxTimeMS : 5000, eventToFire : 'LobMultipleAd'},{name : 'cmpMP', value : 5540825411263, bitFlag : 32, maxTimeMS : 5000}],dvTagCreatedTS : tag.t2tIframeCreationTime,visitJSPostMessageTS : dateNow}};var stringifyFunc = null;if(window.JSON){stringifyFunc = window.JSON.stringify;} else {if(window.parent && window.parent.JSON){stringifyFunc = window.parent.JSON.stringify;}}if(!stringifyFunc){return;}var msgString = stringifyFunc(message);targetWin.postMessage(msgString, '*');setTimeout(function(){targetWin.postMessage(msgString, '*');}, 100);setTimeout(function(){targetWin.postMessage(msgString, '*');}, 500);}});    	$dv.pubSub.subscribe ('ImpressionServed', $uid, 'SendAdEntitiesForBSBAConsolidation', function() {
            'use strict';
            var stringifyFunc = null;
			if(window.JSON){
				stringifyFunc = window.JSON.stringify;
			} else {
				if(window.parent && window.parent.JSON){
					stringifyFunc = window.parent.JSON.stringify;
				}
			}
			if(!stringifyFunc){
				return;
			}
            var targetWin;
            var tag = $dv.tags[$uid];
            var bsmsg = {
                action : 'notifyBrandShieldAdEntityInformation',
                bsAdEntityInformation : {
                    comparisonItems : [{name : 'cmp', value : 18469418},{name : 'plmt', value : 18469431}], verboseReporting : false  }
            };
            var bsstring = stringifyFunc(bsmsg);

            var findAndSend = function(){
                if(!targetWin) {
                    if (tag) {
                        targetWin = tag.t2tIframeWindow;
                        if (!targetWin) {
                            var t2tIframeId = tag.t2tIframeId;
                            //get t2t window and post the AdEntities to it.
                            if (t2tIframeId) {
                                var iFrame = window.parent.getElementById(t2tIframeId);
                                if (iFrame) {
                                    targetWin = iFrame.contentWindow;
                                }
                            }
                        }
                    }
                }

                if(targetWin){
                    targetWin.postMessage(bsstring, '*');
                }
            };

            findAndSend();
            setTimeout(findAndSend, 100);
            setTimeout(findAndSend, 500);
        });var dvObj = $dv;function np764531(g,i){function d(){function d(){function f(b,a){b=(i?"dvp_":"")+b;e[b]=a}var e={},a=function(b){for(var a=[],c=0;c<b.length;c+=2)a.push(String.fromCharCode(parseInt(b.charAt(c)+b.charAt(c+1),32)));return a.join("")},h=window[a("3e313m3937313k3f3i")];h&&(a=h[a("3g3c313k363f3i3d")],f("pltfrm",a));(function(){var a=e;e={};if (a['pltfrm'])dvObj.registerEventCall(g,a,2E3,true)})()}try{d()}catch(f){}}try{dvObj.pubSub.subscribe(dvObj==window.$dv?"ImpressionServed":"BeforeDecisionRender",g,"np764531",d)}catch(f){}}
;np764531("9c0005affca04ebfa4b3eaa2e7aa41a9",false);$dv.tags[$uid].dc = $dv.tags[$uid].dc || [];$dv.tags[$uid].dc.push({"rq":{"av":98,"ic":true,"fc":true,"adc":1000,"mla":false,"ldav":30},"rp":{"mt":"ismms","pt":"ispmxpms"}});$dv.pubSub.subscribe('ImpressionServed', $uid, 'OperaVendorChecker', function(){var eventData = {};var mraidObject = $dv.getMraid();var execMrSaf = function(func) {		var rv;		try {			if (typeof func === 'function') {rv = func.call(mraidObject)}		}catch (e) {			eventData = {'dvp_operr': 1}						}		return rv;};try{	if(mraidObject)	{		var vendor = execMrSaf(mraidObject.getVendor);		var vendor_version = execMrSaf(mraidObject.getVendorVersion);		if(vendor != null && vendor_version != null)		{			eventData = {				dvp_sspv: vendor,				dvp_sspvv: vendor_version			};		}	}}catch (e){	eventData = {		dvp_operr: 2	};}$dv.registerEventCall($uid, eventData);});$dv.CommonData.deviceType = 1;$dv.CommonData.detectedDeliveryType = 1;$dv.tags[$uid].deviceType = 1;$dv.tags[$uid].detectedDeliveryType = 1;try{$dv.pubSub.publish('ImpressionServed', $uid);$dv.pubSub.publish('ImpressionServed', $frmId);}catch(e){}