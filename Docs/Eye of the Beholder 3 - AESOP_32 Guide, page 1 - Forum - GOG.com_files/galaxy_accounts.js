!function(modules){var installedModules={};function __webpack_require__(moduleId){if(installedModules[moduleId])return installedModules[moduleId].exports;var module=installedModules[moduleId]={i:moduleId,l:!1,exports:{}};return modules[moduleId].call(module.exports,module,module.exports,__webpack_require__),module.l=!0,module.exports}__webpack_require__.m=modules,__webpack_require__.c=installedModules,__webpack_require__.d=function(exports,name,getter){__webpack_require__.o(exports,name)||Object.defineProperty(exports,name,{configurable:!1,enumerable:!0,get:getter})},__webpack_require__.n=function(module){var getter=module&&module.__esModule?function(){return module.default}:function(){return module};return __webpack_require__.d(getter,"a",getter),getter},__webpack_require__.o=function(object,property){return Object.prototype.hasOwnProperty.call(object,property)},__webpack_require__.p="",__webpack_require__(__webpack_require__.s=83)}({0:function(module,exports){module.exports=function(src){function log(error){"undefined"!=typeof console&&(console.error||console.log)("[Script Loader]",error)}try{"undefined"!=typeof execScript&&"undefined"!=typeof attachEvent&&"undefined"==typeof addEventListener?execScript(src):"undefined"!=typeof eval?eval.call(null,src):log("EvalError: No eval function available")}catch(error){log(error)}}},83:function(module,__webpack_exports__,__webpack_require__){"use strict";Object.defineProperty(__webpack_exports__,"__esModule",{value:!0});var __WEBPACK_IMPORTED_MODULE_0_script_loader_data_application_src_GOG_Website_CommonBundle_Resources_assets_scripts_vendor_gog_galaxy_accounts_js__=__webpack_require__(84);__webpack_require__.n(__WEBPACK_IMPORTED_MODULE_0_script_loader_data_application_src_GOG_Website_CommonBundle_Resources_assets_scripts_vendor_gog_galaxy_accounts_js__)},84:function(module,exports,__webpack_require__){__webpack_require__(0)(__webpack_require__(85))},85:function(module,exports){module.exports='var GalaxyAccounts=function(){"use strict";var a={is_supporting:{css_animation:!1,css_pseudo_animation:!1},classes:{no_css_animations:"no-cssanimations",no_css_pseudo_animations:"no-csspseudoanimations"},is_css_tested:!1,is_mobile:navigator.userAgent.toLowerCase().indexOf("mobi")!==-1,debounce:function(a,b,c){var d;return function(){var e=this,f=arguments,g=function(){d=null,c||a.apply(e,f)},h=c&&!d;clearTimeout(d),d=setTimeout(g,b),h&&a.apply(e,f)}},addClass:function(a,b){for(var c=a.className.split(" "),d=c.length;d--;)if(b===c[d])return;c.push(b),a.className=c.join(" ")},removeClass:function(a,b){for(var c=a.className.split(" "),d=c.length;d--;)if(b===c[d]){c.splice(d,1);break}a.className=c.join(" ")},addCSS:function(a,b){var c,d;if(c=a.getAttribute("style"),"string"==typeof c){c=c.replace(/;\\s+/g,";"),c=c.replace(/:\\s+/g,":"),c=c.split(";");for(var e=c.length;e--;)d=c[e].split(":"),2===d.length&&"undefined"!=typeof b[d[0]]&&c.splice(e,1)}else c=[];for(var f in b)b.hasOwnProperty(f)&&("number"==typeof b[f]&&0!==b[f]?c.push(f+":"+b[f]+"px"):c.push(f+":"+b[f]));a.setAttribute("style",c.join(";"))},removeCSS:function(a,b){var c,d;if(c=a.getAttribute("style"),"string"==typeof c&&0!==c.length){c=c.replace(/;\\s+/g,";"),c=c.replace(/:\\s+/g,":"),c=c.split(";");for(var e=c.length;e--;)d=c[e].split(":"),2===d.length&&b.indexOf(d[0])!==-1&&c.splice(e,1);a.setAttribute("style",c.join(";"))}},cssTestingFinished:function(a){for(var b in a)a.hasOwnProperty(b)&&"undefined"!=typeof this.is_supporting[b]&&(this.is_supporting[b]=a[b]);this.is_css_tested=!0,this.testCallback&&this.testCallback(this.test_css_calback_arguments)},registerCSSTestCallback:function(a,b){this.is_css_tested&&a(b),this.test_css_calback_arguments=b,this.testCallback=a}};return function(){var b,c=document.createElement("div"),d=document.createElement("style"),e=\'#divForTest{-moz-animation:spin 0.5s linear;-webkit-animation:spin 0.5s linear;animation:spin 0.5s linear;position:absolute;}#divForTest:before{content:"";display:block;height:0;-o-transition:0s 100s;-moz-transition:0s 100s;-webkit-transition:0s 100s;transition:0s 100s;}#divForTest.test:before{height:10px}\',f="Webkit Moz O".split(" ");b=function(){var b={css_animation:!1,css_pseudo_animation:!1};if(void 0!==c.style.animationName&&(b.css_animation=!0),b.css_animation===!1)for(var e=f.length;e--;)if(void 0!==c.style[f[e]+"AnimationName"]){b.css_animation=!0;break}a.addClass(c,"test"),0===c.offsetHeight&&(b.css_pseudo_animation=!0),document.body.removeChild(c),document.body.removeChild(d),a.cssTestingFinished(b)},d.textContent=e,document.body.appendChild(d),c.setAttribute("id","divForTest"),document.body.appendChild(c),setTimeout(b,25)}(),function(b,c,d){function e(a,b,c){var d={};"function"==typeof b&&(d.accountChangeSuccess=b),"function"==typeof c&&(d.close=c,d.goBackToAccount=c),m.open(a+"?action=account_change",null,d)}var f,g,h,i,j,k,l,m;i={MissingPageURL:function(a){this.message="Provided URL is: "+a,this.name="Error: MissingPageURL"}},m=function(b,c,d){var e,f,g,h,m,n,o,p,q,r,s,t,u,v,w,x,y,z,A,B,C,D,E=[],F=b,G=!1,H=/\\bgac=([a-zA-Z\\/0-9\\-_]+)/,I="gog_lc",J=!1,K={height:0,width:0},L={height:0,width:0},M={},N={},O=1;return s=function(){try{C=u(c),z(d)}catch(a){console.log(a)}},z=function(a){if(a){var b=I+"="+a;F+=F.indexOf("?")!=-1?"&"+b:"?"+b}},u=function(a){if(!a)throw new i.MissingPageURL(a);return a.replace(/\\/?$/,"/")},x=function(){var b={for_content:!0,for_window:!0};return{checkIfResized:function(a){return b[a]},setThatNotResized:function(a){b[a]=!1},setThatResized:function(a){b[a]=!0},resizeEvent:a.debounce(function(a){b.for_content=!0,b.for_window=!0,y&&y(a)},300)}}(),q=function(a){return M="scroll"===a?{height:K.height,width:K.width,top:window.pageYOffset,left:window.pageXOffset}:{height:D.offsetTop,width:D.offsetWidth,top:window.pageYOffset,left:window.pageXOffset},O=M.width<K.width?-1:1,K={height:M.height,width:M.width,left:M.left,top:M.top},{dimensions:M,resize_direction:O}},t=function(){var a=window.innerHeight;return N={height:document.documentElement.scrollHeight,width:document.documentElement.scrollWidth},N.height<a&&(N.height=a),L={height:N.height,width:N.width},N},r=function(b){var c,d=document.createElement("style");c="#__BAR_PARAM__ a:not(:hover){background-position:0 100%;background-size:100% 1px!important;background-repeat:repeat-x}@-moz-keyframes __PARAM__-spin{100%{-moz-transform:rotate(360deg);transform:rotate(360deg)}}@-o-keyframes __PARAM__-spin{100%{-o-transform:rotate(360deg);transform:rotate(360deg)}}@-webkit-keyframes __PARAM__-spin{100%{-webkit-transform:rotate(360deg);transform:rotate(360deg)}}@keyframes __PARAM__-spin{100%{-moz-transform:rotate(360deg);-ms-transform:rotate(360deg);-o-transform:rotate(360deg);-webkit-transform:rotate(360deg);transform:rotate(360deg)}}.l-flexible#__PARAM__,.l-mobile#__PARAM__{position:absolute;top:0;z-index:2010;width:100%;height:100%;text-align:center;white-space:nowrap}.l-flexible#__PARAM__:after,.l-mobile#__PARAM__:after{content:\'\';display:inline-block;vertical-align:middle;height:100%;margin-right:-.25em}.l-flexible#__PARAM__:before,.l-mobile#__PARAM__:before{position:absolute}.l-flexible .__PARAM____container,.l-mobile .__PARAM____container{display:inline-block;vertical-align:top;position:relative;padding:15px;margin:-15px}.l-flexible iframe,.l-mobile iframe{-moz-box-shadow:0 0 15px rgba(0,0,0,.15),0 1px 3px rgba(0,0,0,.15);-webkit-box-shadow:0 0 15px rgba(0,0,0,.15),0 1px 3px rgba(0,0,0,.15);box-shadow:0 0 15px rgba(0,0,0,.15),0 1px 3px rgba(0,0,0,.15)}#__PARAM__{position:static;left:0}#__PARAM__:before{content:\'\';width:.1em;height:.1em;-moz-box-shadow:.475em 0 0 #000,.475em -.01em 0 rgba(0,0,0,.99333),.4745em -.02em 0 rgba(0,0,0,.98667),.474em -.03em 0 rgba(0,0,0,.98),.4735em -.0395em 0 rgba(0,0,0,.97333),.4725em -.0495em 0 rgba(0,0,0,.96667),.4715em -.0595em 0 rgba(0,0,0,.96),.47em -.0695em 0 rgba(0,0,0,.95333),.4685em -.079em 0 rgba(0,0,0,.94667),.4665em -.089em 0 rgba(0,0,0,.94),.4645em -.099em 0 rgba(0,0,0,.93333),.4625em -.1085em 0 rgba(0,0,0,.92667),.46em -.118em 0 rgba(0,0,0,.92),.4575em -.1275em 0 rgba(0,0,0,.91333),.4545em -.1375em 0 rgba(0,0,0,.90667),.452em -.147em 0 rgba(0,0,0,.9),.4485em -.156em 0 rgba(0,0,0,.89333),.445em -.1655em 0 rgba(0,0,0,.88667),.4415em -.175em 0 rgba(0,0,0,.88),.438em -.184em 0 rgba(0,0,0,.87333),.434em -.193em 0 rgba(0,0,0,.86667),.43em -.202em 0 rgba(0,0,0,.86),.4255em -.211em 0 rgba(0,0,0,.85333),.421em -.22em 0 rgba(0,0,0,.84667),.416em -.229em 0 rgba(0,0,0,.84),.4115em -.2375em 0 rgba(0,0,0,.83333),.4065em -.246em 0 rgba(0,0,0,.82667),.401em -.2545em 0 rgba(0,0,0,.82),.3955em -.263em 0 rgba(0,0,0,.81333),.39em -.271em 0 rgba(0,0,0,.80667),.3845em -.279em 0 rgba(0,0,0,.8),.3785em -.287em 0 rgba(0,0,0,.79333),.3725em -.295em 0 rgba(0,0,0,.78667),.366em -.303em 0 rgba(0,0,0,.78),.3595em -.3105em 0 rgba(0,0,0,.77333),.353em -.318em 0 rgba(0,0,0,.76667),.3465em -.325em 0 rgba(0,0,0,.76),.3395em -.3325em 0 rgba(0,0,0,.75333),.3325em -.3395em 0 rgba(0,0,0,.74667),.325em -.3465em 0 rgba(0,0,0,.74),.318em -.353em 0 rgba(0,0,0,.73333),.3105em -.3595em 0 rgba(0,0,0,.72667),.303em -.366em 0 rgba(0,0,0,.72),.295em -.3725em 0 rgba(0,0,0,.71333),.287em -.3785em 0 rgba(0,0,0,.70667),.279em -.3845em 0 rgba(0,0,0,.7),.271em -.39em 0 rgba(0,0,0,.69333),.263em -.3955em 0 rgba(0,0,0,.68667),.2545em -.401em 0 rgba(0,0,0,.68),.246em -.4065em 0 rgba(0,0,0,.67333),.2375em -.4115em 0 rgba(0,0,0,.66667),.229em -.416em 0 rgba(0,0,0,.66),.22em -.421em 0 rgba(0,0,0,.65333),.211em -.4255em 0 rgba(0,0,0,.64667),.202em -.43em 0 rgba(0,0,0,.64),.193em -.434em 0 rgba(0,0,0,.63333),.184em -.438em 0 rgba(0,0,0,.62667),.175em -.4415em 0 rgba(0,0,0,.62),.1655em -.445em 0 rgba(0,0,0,.61333),.156em -.4485em 0 rgba(0,0,0,.60667),.147em -.452em 0 rgba(0,0,0,.6),.1375em -.4545em 0 rgba(0,0,0,.59333),.1275em -.4575em 0 rgba(0,0,0,.58667),.118em -.46em 0 rgba(0,0,0,.58),.1085em -.4625em 0 rgba(0,0,0,.57333),.099em -.4645em 0 rgba(0,0,0,.56667),.089em -.4665em 0 rgba(0,0,0,.56),.079em -.4685em 0 rgba(0,0,0,.55333),.0695em -.47em 0 rgba(0,0,0,.54667),.0595em -.4715em 0 rgba(0,0,0,.54),.0495em -.4725em 0 rgba(0,0,0,.53333),.0395em -.4735em 0 rgba(0,0,0,.52667),.03em -.474em 0 rgba(0,0,0,.52),.02em -.4745em 0 rgba(0,0,0,.51333),.01em -.475em 0 rgba(0,0,0,.50667),0 -.475em 0 rgba(0,0,0,.5),-.01em -.475em 0 rgba(0,0,0,.49333),-.02em -.4745em 0 rgba(0,0,0,.48667),-.03em -.474em 0 rgba(0,0,0,.48),-.0395em -.4735em 0 rgba(0,0,0,.47333),-.0495em -.4725em 0 rgba(0,0,0,.46667),-.0595em -.4715em 0 rgba(0,0,0,.46),-.0695em -.47em 0 rgba(0,0,0,.45333),-.079em -.4685em 0 rgba(0,0,0,.44667),-.089em -.4665em 0 rgba(0,0,0,.44),-.099em -.4645em 0 rgba(0,0,0,.43333),-.1085em -.4625em 0 rgba(0,0,0,.42667),-.118em -.46em 0 rgba(0,0,0,.42),-.1275em -.4575em 0 rgba(0,0,0,.41333),-.1375em -.4545em 0 rgba(0,0,0,.40667),-.147em -.452em 0 rgba(0,0,0,.4),-.156em -.4485em 0 rgba(0,0,0,.39333),-.1655em -.445em 0 rgba(0,0,0,.38667),-.175em -.4415em 0 rgba(0,0,0,.38),-.184em -.438em 0 rgba(0,0,0,.37333),-.193em -.434em 0 rgba(0,0,0,.36667),-.202em -.43em 0 rgba(0,0,0,.36),-.211em -.4255em 0 rgba(0,0,0,.35333),-.22em -.421em 0 rgba(0,0,0,.34667),-.229em -.416em 0 rgba(0,0,0,.34),-.2375em -.4115em 0 rgba(0,0,0,.33333),-.246em -.4065em 0 rgba(0,0,0,.32667),-.2545em -.401em 0 rgba(0,0,0,.32),-.263em -.3955em 0 rgba(0,0,0,.31333),-.271em -.39em 0 rgba(0,0,0,.30667),-.279em -.3845em 0 rgba(0,0,0,.3),-.287em -.3785em 0 rgba(0,0,0,.29333),-.295em -.3725em 0 rgba(0,0,0,.28667),-.303em -.366em 0 rgba(0,0,0,.28),-.3105em -.3595em 0 rgba(0,0,0,.27333),-.318em -.353em 0 rgba(0,0,0,.26667),-.325em -.3465em 0 rgba(0,0,0,.26),-.3325em -.3395em 0 rgba(0,0,0,.25333),-.3395em -.3325em 0 rgba(0,0,0,.24667),-.3465em -.325em 0 rgba(0,0,0,.24),-.353em -.318em 0 rgba(0,0,0,.23333),-.3595em -.3105em 0 rgba(0,0,0,.22667),-.366em -.303em 0 rgba(0,0,0,.22),-.3725em -.295em 0 rgba(0,0,0,.21333),-.3785em -.287em 0 rgba(0,0,0,.20667),-.3845em -.279em 0 rgba(0,0,0,.2),-.39em -.271em 0 rgba(0,0,0,.19333),-.3955em -.263em 0 rgba(0,0,0,.18667),-.401em -.2545em 0 rgba(0,0,0,.18),-.4065em -.246em 0 rgba(0,0,0,.17333),-.4115em -.2375em 0 rgba(0,0,0,.16667),-.416em -.229em 0 rgba(0,0,0,.16),-.421em -.22em 0 rgba(0,0,0,.15333),-.4255em -.211em 0 rgba(0,0,0,.14667),-.43em -.202em 0 rgba(0,0,0,.14),-.434em -.193em 0 rgba(0,0,0,.13333),-.438em -.184em 0 rgba(0,0,0,.12667),-.4415em -.175em 0 rgba(0,0,0,.12),-.445em -.1655em 0 rgba(0,0,0,.11333),-.4485em -.156em 0 rgba(0,0,0,.10667),-.452em -.147em 0 rgba(0,0,0,.1),-.4545em -.1375em 0 rgba(0,0,0,.09333),-.4575em -.1275em 0 rgba(0,0,0,.08667),-.46em -.118em 0 rgba(0,0,0,.08),-.4625em -.1085em 0 rgba(0,0,0,.07333),-.4645em -.099em 0 rgba(0,0,0,.06667),-.4665em -.089em 0 rgba(0,0,0,.06),-.4685em -.079em 0 rgba(0,0,0,.05333),-.47em -.0695em 0 rgba(0,0,0,.04667),-.4715em -.0595em 0 rgba(0,0,0,.04),-.4725em -.0495em 0 rgba(0,0,0,.03333),-.4735em -.0395em 0 rgba(0,0,0,.02667),-.474em -.03em 0 rgba(0,0,0,.02),-.4745em -.02em 0 rgba(0,0,0,.01333),-.475em -.01em 0 rgba(0,0,0,.00667);-webkit-box-shadow:.475em 0 0 #000,.475em -.01em 0 rgba(0,0,0,.99333),.4745em -.02em 0 rgba(0,0,0,.98667),.474em -.03em 0 rgba(0,0,0,.98),.4735em -.0395em 0 rgba(0,0,0,.97333),.4725em -.0495em 0 rgba(0,0,0,.96667),.4715em -.0595em 0 rgba(0,0,0,.96),.47em -.0695em 0 rgba(0,0,0,.95333),.4685em -.079em 0 rgba(0,0,0,.94667),.4665em -.089em 0 rgba(0,0,0,.94),.4645em -.099em 0 rgba(0,0,0,.93333),.4625em -.1085em 0 rgba(0,0,0,.92667),.46em -.118em 0 rgba(0,0,0,.92),.4575em -.1275em 0 rgba(0,0,0,.91333),.4545em -.1375em 0 rgba(0,0,0,.90667),.452em -.147em 0 rgba(0,0,0,.9),.4485em -.156em 0 rgba(0,0,0,.89333),.445em -.1655em 0 rgba(0,0,0,.88667),.4415em -.175em 0 rgba(0,0,0,.88),.438em -.184em 0 rgba(0,0,0,.87333),.434em -.193em 0 rgba(0,0,0,.86667),.43em -.202em 0 rgba(0,0,0,.86),.4255em -.211em 0 rgba(0,0,0,.85333),.421em -.22em 0 rgba(0,0,0,.84667),.416em -.229em 0 rgba(0,0,0,.84),.4115em -.2375em 0 rgba(0,0,0,.83333),.4065em -.246em 0 rgba(0,0,0,.82667),.401em -.2545em 0 rgba(0,0,0,.82),.3955em -.263em 0 rgba(0,0,0,.81333),.39em -.271em 0 rgba(0,0,0,.80667),.3845em -.279em 0 rgba(0,0,0,.8),.3785em -.287em 0 rgba(0,0,0,.79333),.3725em -.295em 0 rgba(0,0,0,.78667),.366em -.303em 0 rgba(0,0,0,.78),.3595em -.3105em 0 rgba(0,0,0,.77333),.353em -.318em 0 rgba(0,0,0,.76667),.3465em -.325em 0 rgba(0,0,0,.76),.3395em -.3325em 0 rgba(0,0,0,.75333),.3325em -.3395em 0 rgba(0,0,0,.74667),.325em -.3465em 0 rgba(0,0,0,.74),.318em -.353em 0 rgba(0,0,0,.73333),.3105em -.3595em 0 rgba(0,0,0,.72667),.303em -.366em 0 rgba(0,0,0,.72),.295em -.3725em 0 rgba(0,0,0,.71333),.287em -.3785em 0 rgba(0,0,0,.70667),.279em -.3845em 0 rgba(0,0,0,.7),.271em -.39em 0 rgba(0,0,0,.69333),.263em -.3955em 0 rgba(0,0,0,.68667),.2545em -.401em 0 rgba(0,0,0,.68),.246em -.4065em 0 rgba(0,0,0,.67333),.2375em -.4115em 0 rgba(0,0,0,.66667),.229em -.416em 0 rgba(0,0,0,.66),.22em -.421em 0 rgba(0,0,0,.65333),.211em -.4255em 0 rgba(0,0,0,.64667),.202em -.43em 0 rgba(0,0,0,.64),.193em -.434em 0 rgba(0,0,0,.63333),.184em -.438em 0 rgba(0,0,0,.62667),.175em -.4415em 0 rgba(0,0,0,.62),.1655em -.445em 0 rgba(0,0,0,.61333),.156em -.4485em 0 rgba(0,0,0,.60667),.147em -.452em 0 rgba(0,0,0,.6),.1375em -.4545em 0 rgba(0,0,0,.59333),.1275em -.4575em 0 rgba(0,0,0,.58667),.118em -.46em 0 rgba(0,0,0,.58),.1085em -.4625em 0 rgba(0,0,0,.57333),.099em -.4645em 0 rgba(0,0,0,.56667),.089em -.4665em 0 rgba(0,0,0,.56),.079em -.4685em 0 rgba(0,0,0,.55333),.0695em -.47em 0 rgba(0,0,0,.54667),.0595em -.4715em 0 rgba(0,0,0,.54),.0495em -.4725em 0 rgba(0,0,0,.53333),.0395em -.4735em 0 rgba(0,0,0,.52667),.03em -.474em 0 rgba(0,0,0,.52),.02em -.4745em 0 rgba(0,0,0,.51333),.01em -.475em 0 rgba(0,0,0,.50667),0 -.475em 0 rgba(0,0,0,.5),-.01em -.475em 0 rgba(0,0,0,.49333),-.02em -.4745em 0 rgba(0,0,0,.48667),-.03em -.474em 0 rgba(0,0,0,.48),-.0395em -.4735em 0 rgba(0,0,0,.47333),-.0495em -.4725em 0 rgba(0,0,0,.46667),-.0595em -.4715em 0 rgba(0,0,0,.46),-.0695em -.47em 0 rgba(0,0,0,.45333),-.079em -.4685em 0 rgba(0,0,0,.44667),-.089em -.4665em 0 rgba(0,0,0,.44),-.099em -.4645em 0 rgba(0,0,0,.43333),-.1085em -.4625em 0 rgba(0,0,0,.42667),-.118em -.46em 0 rgba(0,0,0,.42),-.1275em -.4575em 0 rgba(0,0,0,.41333),-.1375em -.4545em 0 rgba(0,0,0,.40667),-.147em -.452em 0 rgba(0,0,0,.4),-.156em -.4485em 0 rgba(0,0,0,.39333),-.1655em -.445em 0 rgba(0,0,0,.38667),-.175em -.4415em 0 rgba(0,0,0,.38),-.184em -.438em 0 rgba(0,0,0,.37333),-.193em -.434em 0 rgba(0,0,0,.36667),-.202em -.43em 0 rgba(0,0,0,.36),-.211em -.4255em 0 rgba(0,0,0,.35333),-.22em -.421em 0 rgba(0,0,0,.34667),-.229em -.416em 0 rgba(0,0,0,.34),-.2375em -.4115em 0 rgba(0,0,0,.33333),-.246em -.4065em 0 rgba(0,0,0,.32667),-.2545em -.401em 0 rgba(0,0,0,.32),-.263em -.3955em 0 rgba(0,0,0,.31333),-.271em -.39em 0 rgba(0,0,0,.30667),-.279em -.3845em 0 rgba(0,0,0,.3),-.287em -.3785em 0 rgba(0,0,0,.29333),-.295em -.3725em 0 rgba(0,0,0,.28667),-.303em -.366em 0 rgba(0,0,0,.28),-.3105em -.3595em 0 rgba(0,0,0,.27333),-.318em -.353em 0 rgba(0,0,0,.26667),-.325em -.3465em 0 rgba(0,0,0,.26),-.3325em -.3395em 0 rgba(0,0,0,.25333),-.3395em -.3325em 0 rgba(0,0,0,.24667),-.3465em -.325em 0 rgba(0,0,0,.24),-.353em -.318em 0 rgba(0,0,0,.23333),-.3595em -.3105em 0 rgba(0,0,0,.22667),-.366em -.303em 0 rgba(0,0,0,.22),-.3725em -.295em 0 rgba(0,0,0,.21333),-.3785em -.287em 0 rgba(0,0,0,.20667),-.3845em -.279em 0 rgba(0,0,0,.2),-.39em -.271em 0 rgba(0,0,0,.19333),-.3955em -.263em 0 rgba(0,0,0,.18667),-.401em -.2545em 0 rgba(0,0,0,.18),-.4065em -.246em 0 rgba(0,0,0,.17333),-.4115em -.2375em 0 rgba(0,0,0,.16667),-.416em -.229em 0 rgba(0,0,0,.16),-.421em -.22em 0 rgba(0,0,0,.15333),-.4255em -.211em 0 rgba(0,0,0,.14667),-.43em -.202em 0 rgba(0,0,0,.14),-.434em -.193em 0 rgba(0,0,0,.13333),-.438em -.184em 0 rgba(0,0,0,.12667),-.4415em -.175em 0 rgba(0,0,0,.12),-.445em -.1655em 0 rgba(0,0,0,.11333),-.4485em -.156em 0 rgba(0,0,0,.10667),-.452em -.147em 0 rgba(0,0,0,.1),-.4545em -.1375em 0 rgba(0,0,0,.09333),-.4575em -.1275em 0 rgba(0,0,0,.08667),-.46em -.118em 0 rgba(0,0,0,.08),-.4625em -.1085em 0 rgba(0,0,0,.07333),-.4645em -.099em 0 rgba(0,0,0,.06667),-.4665em -.089em 0 rgba(0,0,0,.06),-.4685em -.079em 0 rgba(0,0,0,.05333),-.47em -.0695em 0 rgba(0,0,0,.04667),-.4715em -.0595em 0 rgba(0,0,0,.04),-.4725em -.0495em 0 rgba(0,0,0,.03333),-.4735em -.0395em 0 rgba(0,0,0,.02667),-.474em -.03em 0 rgba(0,0,0,.02),-.4745em -.02em 0 rgba(0,0,0,.01333),-.475em -.01em 0 rgba(0,0,0,.00667);box-shadow:.475em 0 0 #000,.475em -.01em 0 rgba(0,0,0,.99333),.4745em -.02em 0 rgba(0,0,0,.98667),.474em -.03em 0 rgba(0,0,0,.98),.4735em -.0395em 0 rgba(0,0,0,.97333),.4725em -.0495em 0 rgba(0,0,0,.96667),.4715em -.0595em 0 rgba(0,0,0,.96),.47em -.0695em 0 rgba(0,0,0,.95333),.4685em -.079em 0 rgba(0,0,0,.94667),.4665em -.089em 0 rgba(0,0,0,.94),.4645em -.099em 0 rgba(0,0,0,.93333),.4625em -.1085em 0 rgba(0,0,0,.92667),.46em -.118em 0 rgba(0,0,0,.92),.4575em -.1275em 0 rgba(0,0,0,.91333),.4545em -.1375em 0 rgba(0,0,0,.90667),.452em -.147em 0 rgba(0,0,0,.9),.4485em -.156em 0 rgba(0,0,0,.89333),.445em -.1655em 0 rgba(0,0,0,.88667),.4415em -.175em 0 rgba(0,0,0,.88),.438em -.184em 0 rgba(0,0,0,.87333),.434em -.193em 0 rgba(0,0,0,.86667),.43em -.202em 0 rgba(0,0,0,.86),.4255em -.211em 0 rgba(0,0,0,.85333),.421em -.22em 0 rgba(0,0,0,.84667),.416em -.229em 0 rgba(0,0,0,.84),.4115em -.2375em 0 rgba(0,0,0,.83333),.4065em -.246em 0 rgba(0,0,0,.82667),.401em -.2545em 0 rgba(0,0,0,.82),.3955em -.263em 0 rgba(0,0,0,.81333),.39em -.271em 0 rgba(0,0,0,.80667),.3845em -.279em 0 rgba(0,0,0,.8),.3785em -.287em 0 rgba(0,0,0,.79333),.3725em -.295em 0 rgba(0,0,0,.78667),.366em -.303em 0 rgba(0,0,0,.78),.3595em -.3105em 0 rgba(0,0,0,.77333),.353em -.318em 0 rgba(0,0,0,.76667),.3465em -.325em 0 rgba(0,0,0,.76),.3395em -.3325em 0 rgba(0,0,0,.75333),.3325em -.3395em 0 rgba(0,0,0,.74667),.325em -.3465em 0 rgba(0,0,0,.74),.318em -.353em 0 rgba(0,0,0,.73333),.3105em -.3595em 0 rgba(0,0,0,.72667),.303em -.366em 0 rgba(0,0,0,.72),.295em -.3725em 0 rgba(0,0,0,.71333),.287em -.3785em 0 rgba(0,0,0,.70667),.279em -.3845em 0 rgba(0,0,0,.7),.271em -.39em 0 rgba(0,0,0,.69333),.263em -.3955em 0 rgba(0,0,0,.68667),.2545em -.401em 0 rgba(0,0,0,.68),.246em -.4065em 0 rgba(0,0,0,.67333),.2375em -.4115em 0 rgba(0,0,0,.66667),.229em -.416em 0 rgba(0,0,0,.66),.22em -.421em 0 rgba(0,0,0,.65333),.211em -.4255em 0 rgba(0,0,0,.64667),.202em -.43em 0 rgba(0,0,0,.64),.193em -.434em 0 rgba(0,0,0,.63333),.184em -.438em 0 rgba(0,0,0,.62667),.175em -.4415em 0 rgba(0,0,0,.62),.1655em -.445em 0 rgba(0,0,0,.61333),.156em -.4485em 0 rgba(0,0,0,.60667),.147em -.452em 0 rgba(0,0,0,.6),.1375em -.4545em 0 rgba(0,0,0,.59333),.1275em -.4575em 0 rgba(0,0,0,.58667),.118em -.46em 0 rgba(0,0,0,.58),.1085em -.4625em 0 rgba(0,0,0,.57333),.099em -.4645em 0 rgba(0,0,0,.56667),.089em -.4665em 0 rgba(0,0,0,.56),.079em -.4685em 0 rgba(0,0,0,.55333),.0695em -.47em 0 rgba(0,0,0,.54667),.0595em -.4715em 0 rgba(0,0,0,.54),.0495em -.4725em 0 rgba(0,0,0,.53333),.0395em -.4735em 0 rgba(0,0,0,.52667),.03em -.474em 0 rgba(0,0,0,.52),.02em -.4745em 0 rgba(0,0,0,.51333),.01em -.475em 0 rgba(0,0,0,.50667),0 -.475em 0 rgba(0,0,0,.5),-.01em -.475em 0 rgba(0,0,0,.49333),-.02em -.4745em 0 rgba(0,0,0,.48667),-.03em -.474em 0 rgba(0,0,0,.48),-.0395em -.4735em 0 rgba(0,0,0,.47333),-.0495em -.4725em 0 rgba(0,0,0,.46667),-.0595em -.4715em 0 rgba(0,0,0,.46),-.0695em -.47em 0 rgba(0,0,0,.45333),-.079em -.4685em 0 rgba(0,0,0,.44667),-.089em -.4665em 0 rgba(0,0,0,.44),-.099em -.4645em 0 rgba(0,0,0,.43333),-.1085em -.4625em 0 rgba(0,0,0,.42667),-.118em -.46em 0 rgba(0,0,0,.42),-.1275em -.4575em 0 rgba(0,0,0,.41333),-.1375em -.4545em 0 rgba(0,0,0,.40667),-.147em -.452em 0 rgba(0,0,0,.4),-.156em -.4485em 0 rgba(0,0,0,.39333),-.1655em -.445em 0 rgba(0,0,0,.38667),-.175em -.4415em 0 rgba(0,0,0,.38),-.184em -.438em 0 rgba(0,0,0,.37333),-.193em -.434em 0 rgba(0,0,0,.36667),-.202em -.43em 0 rgba(0,0,0,.36),-.211em -.4255em 0 rgba(0,0,0,.35333),-.22em -.421em 0 rgba(0,0,0,.34667),-.229em -.416em 0 rgba(0,0,0,.34),-.2375em -.4115em 0 rgba(0,0,0,.33333),-.246em -.4065em 0 rgba(0,0,0,.32667),-.2545em -.401em 0 rgba(0,0,0,.32),-.263em -.3955em 0 rgba(0,0,0,.31333),-.271em -.39em 0 rgba(0,0,0,.30667),-.279em -.3845em 0 rgba(0,0,0,.3),-.287em -.3785em 0 rgba(0,0,0,.29333),-.295em -.3725em 0 rgba(0,0,0,.28667),-.303em -.366em 0 rgba(0,0,0,.28),-.3105em -.3595em 0 rgba(0,0,0,.27333),-.318em -.353em 0 rgba(0,0,0,.26667),-.325em -.3465em 0 rgba(0,0,0,.26),-.3325em -.3395em 0 rgba(0,0,0,.25333),-.3395em -.3325em 0 rgba(0,0,0,.24667),-.3465em -.325em 0 rgba(0,0,0,.24),-.353em -.318em 0 rgba(0,0,0,.23333),-.3595em -.3105em 0 rgba(0,0,0,.22667),-.366em -.303em 0 rgba(0,0,0,.22),-.3725em -.295em 0 rgba(0,0,0,.21333),-.3785em -.287em 0 rgba(0,0,0,.20667),-.3845em -.279em 0 rgba(0,0,0,.2),-.39em -.271em 0 rgba(0,0,0,.19333),-.3955em -.263em 0 rgba(0,0,0,.18667),-.401em -.2545em 0 rgba(0,0,0,.18),-.4065em -.246em 0 rgba(0,0,0,.17333),-.4115em -.2375em 0 rgba(0,0,0,.16667),-.416em -.229em 0 rgba(0,0,0,.16),-.421em -.22em 0 rgba(0,0,0,.15333),-.4255em -.211em 0 rgba(0,0,0,.14667),-.43em -.202em 0 rgba(0,0,0,.14),-.434em -.193em 0 rgba(0,0,0,.13333),-.438em -.184em 0 rgba(0,0,0,.12667),-.4415em -.175em 0 rgba(0,0,0,.12),-.445em -.1655em 0 rgba(0,0,0,.11333),-.4485em -.156em 0 rgba(0,0,0,.10667),-.452em -.147em 0 rgba(0,0,0,.1),-.4545em -.1375em 0 rgba(0,0,0,.09333),-.4575em -.1275em 0 rgba(0,0,0,.08667),-.46em -.118em 0 rgba(0,0,0,.08),-.4625em -.1085em 0 rgba(0,0,0,.07333),-.4645em -.099em 0 rgba(0,0,0,.06667),-.4665em -.089em 0 rgba(0,0,0,.06),-.4685em -.079em 0 rgba(0,0,0,.05333),-.47em -.0695em 0 rgba(0,0,0,.04667),-.4715em -.0595em 0 rgba(0,0,0,.04),-.4725em -.0495em 0 rgba(0,0,0,.03333),-.4735em -.0395em 0 rgba(0,0,0,.02667),-.474em -.03em 0 rgba(0,0,0,.02),-.4745em -.02em 0 rgba(0,0,0,.01333),-.475em -.01em 0 rgba(0,0,0,.00667);position:fixed;top:3.5em;left:50%;z-index:2010;vertical-align:middle;margin:-.05em 0 0 -.05em;opacity:.45;font-size:70px;-moz-border-radius:50%;-webkit-border-radius:50%;border-radius:50%;-moz-animation:__PARAM__-spin .7s linear infinite;-o-animation:__PARAM__-spin .7s linear infinite;-webkit-animation:__PARAM__-spin .7s linear infinite;animation:__PARAM__-spin .7s linear infinite;-moz-transition:translate3d(0,0,0);-o-transition:translate3d(0,0,0);-webkit-transition:translate3d(0,0,0);transition:translate3d(0,0,0)}.no-cssanimations#__PARAM__:before,.no-csspseudoanimations#__PARAM__:before{width:32px;height:32px;margin-left:-16px;-moz-box-shadow:none;-webkit-box-shadow:none;box-shadow:none;background:url(https://login.gog.com/bundles/gogloginlogin/images/flb-modal-spin.gif)}.__PARAM____container{position:fixed;top:0;left:0;right:0;bottom:0;z-index:2030;overflow:hidden;opacity:0;-moz-transition:opacity .15s linear;-o-transition:opacity .15s linear;-webkit-transition:opacity .15s linear;transition:opacity .15s linear;-moz-transform:translate3d(0,0,0);-ms-transform:translate3d(0,0,0);-o-transform:translate3d(0,0,0);-webkit-transform:translate3d(0,0,0);transform:translate3d(0,0,0)}.__PARAM____container iframe{display:block;width:100%;height:100%;background:0 0;border:none}.__PARAM____overlay{position:fixed;top:0;left:0;bottom:0;right:0;z-index:2000;background:rgba(204,204,204,.5)}.__PARAM____measure{position:fixed;bottom:0;left:0;right:0}.__PARAM____measure.no-cssanimations{background:url(https://login.gog.com/bundles/gogloginlogin/images/flb-modal-spin.gif)}.l-mobile .__PARAM____container{margin-top:130px}.l-mobile.__PARAM____overlay{position:absolute}.l-small-screen#__PARAM__:before{top:50%;margin-top:-.05em}.l-small-screen>.__PARAM____container{vertical-align:middle;margin-top:-15px}.l-loaded#__PARAM__:before{content:none}.l-loaded .__PARAM____container{opacity:1}#__BAR_PARAM__{position:fixed;bottom:0;left:0;width:100%;height:auto;z-index:2040;background-color:rgba(222,222,222,.9);color:#595959;font-size:.75rem;line-height:1.5;padding:.5rem 1rem;-moz-box-sizing:border-box;-webkit-box-sizing:border-box;box-sizing:border-box;-moz-box-shadow:0 0 15px rgba(0,0,0,.15),0 1px 3px rgba(0,0,0,.15);-webkit-box-shadow:0 0 15px rgba(0,0,0,.15),0 1px 3px rgba(0,0,0,.15);box-shadow:0 0 15px rgba(0,0,0,.15),0 1px 3px rgba(0,0,0,.15);text-align:center}#__BAR_PARAM__ a:not(:hover){background-image:-webkit-gradient(linear,0 50%,100% 50%,color-stop(0%,currentColor),color-stop(100%,currentColor));background-image:-moz-linear-gradient(left,currentColor,currentColor);background-image:-o-linear-gradient(left,currentColor,currentColor);background-image:-webkit-linear-gradient(left,currentColor,currentColor);background-image:linear-gradient(to right,currentColor,currentColor)}#__BAR_PARAM__Content{max-width:1060px;display:inline-block;vertical-align:middle;text-align:left}",c=c.replace(/__PARAM__/g,b),c=c.replace(/__BAR_PARAM__/g,k.getWrapperId()),d.setAttribute("media","screen"),d.textContent=c,document.body.appendChild(d),D=document.createElement("div"),a.addClass(D,b+"__measure"),a.is_supporting.css_animation&&a.is_supporting.css_pseudo_animation||a.addClass(D,a.classes.no_css_animations),document.body.appendChild(D),q()},m=function(a){if(!J&&(J=!0,0!==E.length))for(var b=E.length;b--;)E[b](a)},n=a.debounce(m,50),w=function(a){return a.replace(/^[\\/]*/,"")},h=function(a,b,c){var d=F;a&&(d=C+w(a)),A="object"==typeof c?c:{},l.setContentType(b),g(),j.create(d),o()},g=function(){j.remove()},f=function(){l.resetSubmissionTracking(),g(),k.destroy(),p()},e=function(a){27===a.which&&f()},v=function(){var a,b;return a=window.decodeURIComponent(window.location.hash),(b=a.match(H))?(B=b[1],window.location.hash="",void(G=!0)):G=!1},o=function(){window.addEventListener("scroll",n,!1),window.addEventListener("keydown",e,!1),window.addEventListener("resize",x.resizeEvent,!1)},p=function(){window.removeEventListener("scroll",n,!1),window.removeEventListener("keydown",e,!1),window.removeEventListener("resize",x.resizeEvent,!1)},s(),{init:function(){v(),a.registerCSSTestCallback(function(){r(j.getRootId()),G&&h(B)})},open:h,close:function(){f()},removeWindowsEventListener:function(a,b){window.removeEventListener(a,b)},setWindowsEventListener:function(a,b){window.addEventListener(a,b,!1)},getContentDimensions:function(){return x.checkIfResized("for_content")?(x.setThatNotResized("for_content"),t()):L},getLastResizeDirection:function(){return O},beforeIframeReload:function(){x.setThatResized("for_content"),x.setThatResized("for_window")},getWindowDimensions:function(){return x.checkIfResized("for_window")?(x.setThatNotResized("for_window"),q()):{dimensions:K}},registerWindowResizeCallback:function(a){y=a},deregisterWindowResizeCallback:function(){y=void 0},registerScrollCallback:function(a){E.push(a)},deregisterScrollCallback:function(a){var b=E.indexOf(a);b!==-1&&E.splice(b,1)},fireResizeEvent:function(){x.resizeEvent()},getAuthURL:function(){return F},getMeasureWidth:function(){return D.offsetWidth},getMessageCallbacks:function(){return A},addMessageCallback:function(a,b){A[a]=b}}}(b,c,d),f=function(){var b,c,d,e,f,g,h,i,j={root:null,iframe:null,overlay:null,frameHTML:null},k="GalaxyAccountsFrame",n="GalaxyAccountsFrameContainer",o={ids:{root:n,iframe:k},classes:{overlay_element:n+"__overlay",container_element:n+"__container",is_small_screen_reached:"l-small-screen",is_flexible_layout:"l-flexible",is_frame_loaded:"l-loaded",is_mobile:"l-mobile"},minimal_height:0,height_small_screen:600,is_debug:!1,is_frame_loaded:!1,is_open:!1,is_fixed:!1,iframe_boundaries:{has_biggest_boundary:!1,has_smallest_boundary:!1,is_boundary_reached:!1,lowBoundary:null,highBoundary:null}};i=function(){var b,c,d,e,f,g,h,i=!1;return e=function(){a.addCSS(j.overlay,m.getContentDimensions())},f=function(){var b,c,d=!1,e=!1,f=!1;return b=function(){d=!1,e=!1,f=!1},c=function(){var b,c,d,e,f,g,i,k,l;b=m.getWindowDimensions().dimensions,d=b.height,g=j.root.style.top,g=g?parseInt(g,10):0,i=h.top+g,l=i+h.height,k=b.top+d,e=l>k,f=i<b.top,c=!e&&!f,c||(g=b.top-h.top,g>=0?a.addCSS(j.root,{top:g}):(a.addCSS(j.root,{top:0}),window.scrollTo(b.left,h.top)))},{blurOccurred:function(){b(),d=!0},focusOccurred:function(){d&&(e=!0,g())},monitorUserTouch:function(){b()},scrollToInput:c,adjustPosition:function(){e&&d&&o.is_fixed}}}(),g=a.debounce(f.adjustPosition,300),d=function(){var b,c,d,k,n,p;return d=function(){var b=m.getWindowDimensions(),c=o.is_fixed&&j.iframe.offsetWidth!==b.dimensions.width,d=b.dimensions.height,e=b.dimensions.top;l.sendMessage({action:"viewportResize",data:b}),o.is_fixed&&!c||(a.addCSS(j.root,{width:b.dimensions.width,height:d,top:e,left:b.dimensions.left}),a.addCSS(j.container,{height:b.dimensions.height,width:b.dimensions.width}),i&&f.scrollToInput()),l.sendMessage({action:"iframeResize",data:{}})},c=function(){var a=m.getWindowDimensions().dimensions.height;if(!(a<o.minimal_height)||o.is_fixed)return a<o.minimal_height?(o.is_fixed=!1,void b("flexible")):void(o.is_fixed&&a<=o.minimal_height||(o.is_fixed=!0,b("fixed")))},k=function(){return n?(p=m.getMeasureWidth(),n!==p&&(n=p,m.fireResizeEvent())):(n=m.getMeasureWidth(),m.fireResizeEvent())},b=function(b){return"flexible"===b?(d(),void a.addClass(j.root,o.classes.is_flexible_layout)):(a.removeClass(j.root,o.classes.is_flexible_layout),a.removeCSS(j.root,["height","width","left","top"]),void a.removeCSS(j.container,["height","width"]))},{initDOM:function(){e()},htmlGeneration:function(){},registerContentDimensions:function(b){o.minimal_height=b.dimensions.height,o.minimal_width=b.dimensions.width,o.is_fixed||a.addCSS(j.container,b.dimensions),c()},registerFocusedInputPosition:function(a){h=a,i=!0,m.setWindowsEventListener("touchstart",f.monitorUserTouch),m.setWindowsEventListener("mousedown",f.monitorUserTouch),m.registerScrollCallback(g),f.focusOccurred()},deregisterFocusedInputPosition:function(){i=!1,f.blurOccurred(),m.deregisterScrollCallback(g),m.removeWindowsEventListener("touchstart",f.monitorUserTouch),m.removeWindowsEventListener("mousedown",f.monitorUserTouch)},loadContent:function(){o.is_fixed=!0,d()},scrollWindow:a.debounce(k,150),resizeWindow:function(){e(),d()}}}(),c=function(){var b,c,d;return d=function(){},b=function(b){l.sendMessage({action:"viewportResize",data:b.dimensions}),a.addCSS(j.iframe,{width:b.dimensions.width}),l.sendMessage({action:"iframeResize",data:{}})},c=function(){e();var b=m.getWindowDimensions().dimensions,c=m.getContentDimensions(),d=b.top,f=b.left,g=b.width,h=b.height;f+g>c.width&&(f-=f+g-c.width),a.addCSS(j.root,{width:g,height:h,top:d,left:f}),h<=o.height_small_screen?a.addClass(j.root,o.classes.is_small_screen_reached):a.removeClass(j.root,o.classes.is_small_screen_reached)},{initDOM:function(){e()},htmlGeneration:function(b){var c=m.getWindowDimensions();a.addCSS(b,c.dimensions)},registerContentDimensions:function(b){a.addCSS(j.iframe,b.dimensions),a.addCSS(j.container,b.dimensions)},registerFocusedInputPosition:function(a){h=a,i=!0,m.setWindowsEventListener("touchstart",f.monitorUserTouch),m.registerScrollCallback(g),f.focusOccurred()},deregisterFocusedInputPosition:function(){i=!1,f.blurOccurred(),m.deregisterScrollCallback(g),m.removeWindowsEventListener("touchstart",f.monitorUserTouch)},loadContent:function(){var a=m.getWindowDimensions();c(),b(a)},scrollWindow:a.debounce(d,500),resizeWindow:function(){return}}}(),b=a.is_mobile?c:d}(),b=function(){d=function(){}},c=i.resizeWindow,g=function(){m.registerWindowResizeCallback(c),m.registerScrollCallback(i.scrollWindow),j.root.addEventListener("click",m.close,!1),j.overlay.addEventListener("click",m.close,!1),i.initDOM(),j.iframe.onload=f},h=function(){m.deregisterWindowResizeCallback(),m.deregisterScrollCallback(i.scrollWindow)},e=function(b){var c,d,e,f,g;return j.frameHTML?(g=j.frameHTML.cloneNode(!0),g.querySelector("iframe").src=b,g):(c=document.createElement("iframe"),d=document.createElement("div"),e=document.createElement("div"),f=document.createElement("div"),g=document.createDocumentFragment(),f.setAttribute("id",o.ids.root),a.is_mobile&&(a.addClass(f,o.classes.is_mobile),\na.addClass(e,o.classes.is_mobile)),a.is_supporting.css_animation||a.addClass(f,a.classes.no_css_animations),a.is_supporting.css_pseudo_animation||a.addClass(f,a.classes.no_css_pseudo_animations),a.addClass(e,o.classes.overlay_element),c.setAttribute("id",o.ids.iframe),c.setAttribute("src",b),c.setAttribute("frameborder","0"),a.addClass(d,o.classes.container_element),d.appendChild(c),f.appendChild(d),g.appendChild(e),i.htmlGeneration(f),g.appendChild(f.cloneNode(!0)),j.frameHTML=g,g.cloneNode(!0))},this.firstIframeLoad=function(){l.registerFrameWindow()},this.onIframesContentLoad=function(){i.loadContent()},this.iframeInputfocused=function(a){i.registerFocusedInputPosition(a)},this.iframeInputBlured=function(){i.deregisterFocusedInputPosition()},this.beforeIframeLocationChange=function(b){o.is_frame_loaded=!1,m.beforeIframeReload(),a.removeClass(j.root,o.classes.is_frame_loaded),setTimeout(function(){l.sendMessage({action:"proceedWithLocationChange",data:{event:b.event}})},150)},this.registerContentDimensions=function(b){var c,d=b.boundary_info;switch(d.is_boundary_reached&&(o.iframe_boundaries[d.boundary_type]=b.dimensions.width,o.iframe_boundaries.is_boundary_reached=!0),d.boundary_type){case"highBoundary":o.iframe_boundaries.has_biggest_boundary=!0,o.iframe_boundaries.has_smallest_boundary=!1;break;case"lowBoundary":o.iframe_boundaries.has_biggest_boundary=!1,o.iframe_boundaries.has_smallest_boundary=!0;break;default:o.iframe_boundaries.has_biggest_boundary=!1,o.iframe_boundaries.has_smallest_boundary=!1}i.registerContentDimensions(b),o.is_frame_loaded||(o.is_frame_loaded=!0,a.addClass(j.root,o.classes.is_frame_loaded),c={action:"containerIsReady",data:{}},l.sendMessage(c))},this.create=function(a){m.beforeIframeReload(),document.body.appendChild(e(a)),j.iframe=document.getElementById(o.ids.iframe),j.root=document.getElementById(o.ids.root),j.container=j.root.querySelector("."+o.classes.container_element),j.overlay=document.querySelector("."+o.classes.overlay_element),l.activate(),g(),o.is_open=!0},this.remove=function(){o.is_open&&(document.body.removeChild(j.root),document.body.removeChild(j.overlay),h(),j.root=null,j.iframe=null,o.is_frame_loaded=!1,o.is_open=!1,l.deactivate())},this.getFrameWindow=function(){return!!j.iframe&&j.iframe.contentWindow},this.getRootId=function(){return o.ids.root},b()},g=function(){var a,b={wrapperId:"GalaxyAccountsMessageBar",contentId:"GalaxyAccountsMessageBarContent",node:null};a=function(a){var c,d;return d=document.createElement("div"),d.setAttribute("id",b.contentId),d.innerHTML=a,c=document.createElement("div"),c.setAttribute("id",b.wrapperId),c.appendChild(d.cloneNode(!0)),c.cloneNode(!0)},this.create=function(c){null!==b.node?document.getElementById(b.contentId).innerHTML=c:(b.node=a(c),document.body.appendChild(b.node))},this.destroy=function(){null!==b.node&&(document.body.removeChild(b.node),b.node=null)},this.getWrapperId=function(){return b.wrapperId}},h=function(a,b){var c,d,e,f,g,h,i,k=null,l="loginForm",n="*";return h=function(a){l=a||l},i=function(){return k?k:l},f=function(){return window.location.origin?window.location.origin:window.location.protocol+"//"+window.location.hostname+(window.location.port?window.location.port:"")},g=function(a){try{c.postMessage(JSON.stringify(a),n)}catch(a){console.log(a)}},d=function(a){var c;if(b.getFrameWindow()&&a.source===b.getFrameWindow()){try{c=JSON.parse(a.data)}catch(a){return}c&&c.action&&e(c)}},e=function(c){switch(c.action){case"close":a.close();break;case"reload":k=null,window.top.location.reload();break;case"registerContentDimensions":b.registerContentDimensions(c.data);break;case"firstIframeLoad":n=c.data.origin,b.firstIframeLoad(c.data);break;case"contentLoaded":j.onIframesContentLoad();break;case"formSubmission":k=c.data.formType;break;case"inputFocused":b.iframeInputfocused(c.data);break;case"inputBlured":b.iframeInputBlured();break;case"beforeIframeLocationChange":b.beforeIframeLocationChange(c.data),k=null,h(c.data.contentType)}var d=m.getMessageCallbacks();for(var e in d)if(e===c.action){d[e](c.data);break}},{activate:function(){m.setWindowsEventListener("message",d)},resetSubmissionTracking:function(){k=null},deactivate:function(){m.removeWindowsEventListener("message",d)},registerFrameWindow:function(){c=b.getFrameWindow(),g({action:"registerOrigin",data:{origin:f()}}),g({action:"loadContent",data:{contentType:i()}})},setContentType:h,sendMessage:g}},this.openInfoBar=function(a){k.create(a)},this.closeInfoBar=function(){k.destroy()},this.openLoginForm=function(){m.open(null,"loginForm")},this.openRegistrationForm=function(){m.open(null,"registerForm")},this.openAccount=function(){m.open("account")},this.openAvatarChange=function(a,b){e("/account",a,b)},this.openEmailChange=function(a,b){e("/account/email",a,b)},this.openPasswordChange=function(a,b){e("/account/password",a,b)},this.openTwoStepEnable=function(a,b){e("/account/two_step/enable",a,b)},this.openTwoStepDisable=function(a,b){e("/account/two_step/disable",a,b)},this.onExternalProviderFlow=function(a){m.addMessageCallback("externalProviderFlow",a)},this.open=function(a,b){a?m.open(a,b):m.open(null,b)},this.close=function(){m.close()},k=new g,j=new f,l=new h(this,j),m.init()}}();'}});