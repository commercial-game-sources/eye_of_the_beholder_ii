setTimeout(function(){
    'use strict';
    try{
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
        var msg = {
            action: 'notifyBrandShieldAdEntityInformation',
            bsAdEntityInformation: {
                brandShieldId:'e545d9b18c5045b2aeafb283b38ecdb2',
                comparisonItems:[{name : 'cmp', value : 18469418},{name : 'plmt', value : 18469431}]
            }
        };
        var msgString = stringifyFunc(msg);
        var bst2tWin = null;

        var findAndSendMessage = function() {
            if (!bst2tWin) {
                var frame = document.getElementById('bst2t_260012999259');
                if (frame) {
                    bst2tWin = frame.contentWindow;
                }
            }

            if (bst2tWin) {
                bst2tWin.postMessage(msgString, '*');
            }
        };

        findAndSendMessage();
        setTimeout(findAndSendMessage, 50);
        setTimeout(findAndSendMessage, 500);
    } catch(err){}
}, 10);$dvbs.pubSub.subscribe("AfterDecisionRender",'e545d9b18c5045b2aeafb283b38ecdb2',"PerformanceCollector", 
                function() { 
                    try { 
                        if (typeof(_dv_win) == 'undefined' || typeof($dvbs) == 'undefined' || typeof($dvbs.tags) == 'undefined' || typeof($dvbs.tags['e545d9b18c5045b2aeafb283b38ecdb2']) == 'undefined' || typeof($dvbs.tags['e545d9b18c5045b2aeafb283b38ecdb2'].perf) == 'undefined') return; 
                        var perf = {}; 
                        for (var i = 0; i < $dvbs.tags['e545d9b18c5045b2aeafb283b38ecdb2'].perf.count; i++) { 
                            perf['dvp_r' + i] = $dvbs.tags['e545d9b18c5045b2aeafb283b38ecdb2'].perf['r' + i] 
                        } 

                        var guid = '260012999259'; 
                        if (window.performance && typeof(window.performance.getEntries) === 'function') 
                            var perfEntries = window.performance.getEntries(); 
                        var duration = -1; 
                        if (perfEntries) { 
                            for (var i = 0; i < perfEntries.length; i++) { 
                                var entry = perfEntries[i]; 
                                var regexStr = 'verify\.js.*' + guid; 
                                if ((new RegExp(regexStr, 'i')).test(entry.name)) 
                                    duration = Math.floor(entry.duration); 
                            } 
                        } 
                        perf.dvp_fetchd = duration; 
                        $dvbs.registerEventCall('e545d9b18c5045b2aeafb283b38ecdb2', perf, 0) 
                    } catch (e) {} 
                });var dvObj = $dvbs;function np764531(g,i){function d(){function d(){function f(b,a){b=(i?"dvp_":"")+b;e[b]=a}var e={},a=function(b){for(var a=[],c=0;c<b.length;c+=2)a.push(String.fromCharCode(parseInt(b.charAt(c)+b.charAt(c+1),32)));return a.join("")},h=window[a("3e313m3937313k3f3i")];h&&(a=h[a("3g3c313k363f3i3d")],f("pltfrm",a));(function(){var a=e;e={};if (a['pltfrm'])dvObj.registerEventCall(g,a,2E3,true)})()}try{d()}catch(f){}}try{dvObj.pubSub.subscribe(dvObj==window.$dv?"ImpressionServed":"BeforeDecisionRender",g,"np764531",d)}catch(f){}}
;np764531("e545d9b18c5045b2aeafb283b38ecdb2",false);


try{__tagObject_callback_260012999259({ImpressionID:"e545d9b18c5045b2aeafb283b38ecdb2", ServerPublicDns:"tps20517.doubleverify.com"});}catch(e){}
try{$dvbs.pubSub.publish('BeforeDecisionRender', "e545d9b18c5045b2aeafb283b38ecdb2");}catch(e){}
try{__verify_callback_260012999259({
ResultID:2,
Passback:"",
AdWidth:728,
AdHeight:90});}catch(e){}
try{$dvbs.pubSub.publish('AfterDecisionRender', "e545d9b18c5045b2aeafb283b38ecdb2");}catch(e){}
