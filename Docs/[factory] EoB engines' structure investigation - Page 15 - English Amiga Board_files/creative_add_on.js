//Version: 2.4.2
!function(){function t(e,r,i){function n(o,c){if(!r[o]){if(!e[o]){var f="function"==typeof require&&require;if(!c&&f)return f(o,!0);if(a)return a(o,!0);var u=new Error("Cannot find module '"+o+"'");throw u.code="MODULE_NOT_FOUND",u}var s=r[o]={exports:{}};e[o][0].call(s.exports,function(t){var r=e[o][1][t];return n(r||t)},s,s.exports,t,e,r,i)}return r[o].exports}for(var a="function"==typeof require&&require,o=0;o<i.length;o++)n(i[o]);return n}return t}()({1:[function(t,e,r){var i=function(){"use strict";var t="creative_add_on.js";Array.prototype.indexOf||(Array.prototype.indexOf=function(t,e){var r;if(null==this)throw new TypeError('"this" is null or not defined');var i=Object(this),n=i.length>>>0;if(0===n)return-1;var a=+e||0;if(Math.abs(a)===1/0&&(a=0),a>=n)return-1;for(r=Math.max(a>=0?a:n-Math.abs(a),0);r<n;){if(r in i&&i[r]===t)return r;r++}return-1}),Array.prototype.forEach||(Array.prototype.forEach=function(t,e){var r,i;if(null==this)throw new TypeError(" this is null or not defined");var n=Object(this),a=n.length>>>0;if("function"!=typeof t)throw new TypeError(t+" is not a function");for(arguments.length>1&&(r=e),i=0;i<a;){var o;i in n&&(o=n[i],t.call(r,o,i,n)),i++}});var e=function(){var e={},r=document.getElementsByTagName("script");return[].forEach.call(r,function(r){var i=r.getAttribute("src");i&&i.indexOf(t)>-1&&(e.creativeAddonScriptTag=r,e.src=i)}),e},r=function(){var t=document.getElementsByTagName("img");return[].forEach.call(t,function(t){var e=t.getAttribute("src");if(e&&e.indexOf("w55c.net/a.gif")>-1)return e}),null},i=function(t,e){if(!t)return{};var r=e?e:{},i=t.split("?");if(i=i.length>1?i[1]:null){var n=i.split("&");n.forEach(function(t){var e=t.split("="),i=e[0],n=e[1];n&&(r[i]=n)})}return r},n=function(e){if(!e)return"";var r;return r=e.indexOf(t)>-1?e.split(t)[0]:"https://cti.w55c.net/ct/"},a=function(t,e){if(t.w&&t.h&&t.ei){var r="",i=0,n=0,a=0;if(t.ob&&"1"==t.ob&&(i=1),t.ob&&"2"==t.ob&&(a=1),t.pa&&t.ci&&(n=1),i||n||a){if(n)r=[e,"political/pa_icon.js?pos=",t.pos,"&h=",t.h,"&w=",t.w,"&pa=",t.pa,"&beh=",i,"&ci=",t.ci].join("");else{t.pos||(t.pos="top-right");var o={1:{"bottom-left":"2529","bottom-right":"2530","top-left":"2531","top-right":"2532"},2:{"bottom-left":"16741","bottom-right":"16740","top-left":"16742","top-right":"16743"}};r=["//c.evidon.com/durly.js?;coid=292;nid=",o[t.ob][t.pos],";ad_w=",t.w,";ad_h=",t.h].join(""),t.zindex&&(r=r+";ad_z="+t.zindex)}return r}}},o=function(){var t=window.location.pathname.match(/(0R.*?)_/);return t&&t[1]||null},c=function(t){var e='<script async=true src="https://z.moatads.com/dataxudisplay424185025033/moatad.js#moatClientLevel1=[[[ai]]]&moatClientLevel2=[[[ci]]]&moatClientLevel3=[[[fiu]]]&moatClientLevel4=[[[ciu]]]&moatClientSlicer1=[[[epid]]]&moatClientSlicer2=[[[sd]]]&zMoatExchangeID=[[[ei]]]&zMoatDevice=[[[dt]]]&zMoatSite_URL=[[[s]]]&zMoatBundleID=[[[abn]]]&zMoatDealID=[[[dl]]]" type="text/javascript"></script>',r=["ai","fiu","ci","epid","sd","ei","dt","ciu","s","abn","dl"];if(t.ciu||(t.ciu=o()),r.forEach(function(r){var i="UNKNOWN";t[r]&&(i=t[r]),e=e.replace("[[["+r+"]]]",i)}),e.indexOf("[[[")!==-1){var i=e.substr(e.indexOf("[[[")+3);throw i=i.substr(0,i.indexOf("]]]")),new Error("unreplaced Moat parameter:"+i)}return e},f=function(t){if("1"==t.dvt){var e=u("wfivefivec"),r=e?e[1]:null;return["https://cdn.doubleverify.com/dvtp_src.js?ctx=1043655&cmp=2350289&sid=dataxu&plc=2350289&advid=2026610&adsrv=89&btreg=&btadsrv=&tagtype=&dvtagver=6.1.src&DVP_PP_REP=1&DVP_IQM_ID=17&DVPX_PP_IMP_ID=",t.btid,"&DVP_PP_PRICE_PAID=",t.wp_exchange,"&DVP_DV_TT=1&DVP_DV_CT=1&DVP_DX_1=",t.ai,"&DVP_DX_2=",t.ci,"&DVP_DX_3=",t.fiu,"&DVP_DX_4=",t.ciu,"&DVP_DX_5=",t.ei,"&DVP_DX_6=",t.epid,"&DVP_DX_7=",t.esid,"&DVP_DX_8=",r,"&turl=",t.s,"&DVP_PP_BUNDLE_ID=",t.abn,"&DVP_PP_APP_NAME=",t.ean].join("")}},u=function(t){var e=document.cookie.match("(?:^|;[ \t]*)"+t+"=([^;]*)(?:;|$)");return e?e:null},s=function(t){var e=new Date,r=864e5;return e.setTime(r*t+e.getTime()),e},d=function(t){if(t.ei&&"YAHOO"!==t.ei){var e=["AT","BE","BG","HR","QA","CZ","DK","EE","FI","FR","DE","GR","HU","IS","IE","IT","LV","LI","LT","LU","MT","NL","NO","PL","RO","SK","SI","ES","SE","GB"];if(!(!t.c||e.indexOf(t.c)>=0||t.dcn&&e.indexOf(t.dcn)>=0)){var r=u("testuser"),i=['<iframe async=true width="0" height="0" border="0" frameborder="0"',' src="https://cti.w55c.net/ct/cee/AB/cms-2c.html?ei=',t.ei,'" style="display:none;" ></iframe>'].join(""),n=['<iframe async=true width="0" height="0" border="0" frameborder="0"',' src="https://cti.w55c.net/ct/cms-2c.html?ei=',t.ei,'" style="display:none;" ></iframe>'].join("");return r?i:u("wfivefivec")||1!==Math.floor(1e3*Math.random())?n:(document.cookie="testuser=1; expires="+s(30)+"; path=/; domain=.w55c.net",i)}}},l=function(){var t,o,u,s,l=e(),p={},m=window.location.href;if(m&&m.indexOf(".w55c.net")>-1?p=i(m):(m=r(),m&&(p=i(m))),p=i(l.src,p),t=n(l.src),o=a(p,t),u=c(p),s=f(p),o){var h=document.createElement("script");h.async=!0,h.type="text/javascript",h.src=o;var v=document.getElementsByTagName("script")[0];v.parentNode.insertBefore(h,v)}if(s){var _=document.createElement("script");_.async=!0,_.type="text/javascript",_.src=s;var D=document.getElementsByTagName("script")[0];D.parentNode.insertBefore(_,D)}var g=d(p);g&&document.write(g),u&&("1"==p.moat||Math.floor(100*Math.random())<15)&&document.write(u)};return{execute:l}}();try{i.execute()}catch(n){if(1===Math.floor(1e3*Math.random())){var a=document.createElement("img");a.onload=function(){},a.src="https://tags.w55c.net/rs?id=d9f6b05a6b7f4048be552ee87d71eb7a&t=marketing&cetest="+n.message}}},{}]},{},[1]);
//# sourceMappingURL=creative_add_on.js.map