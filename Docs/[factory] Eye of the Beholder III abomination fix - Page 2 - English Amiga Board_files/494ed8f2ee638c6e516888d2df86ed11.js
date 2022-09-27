(function(){/*

 Copyright The Closure Library Authors.
 SPDX-License-Identifier: Apache-2.0
*/
'use strict';var e=this||self;
function g(a){var b=typeof a;if("object"==b)if(a){if(a instanceof Array)return"array";if(a instanceof Object)return b;var c=Object.prototype.toString.call(a);if("[object Window]"==c)return"object";if("[object Array]"==c||"number"==typeof a.length&&"undefined"!=typeof a.splice&&"undefined"!=typeof a.propertyIsEnumerable&&!a.propertyIsEnumerable("splice"))return"array";if("[object Function]"==c||"undefined"!=typeof a.call&&"undefined"!=typeof a.propertyIsEnumerable&&!a.propertyIsEnumerable("call"))return"function"}else return"null";else if("function"==
b&&"undefined"==typeof a.call)return"object";return b}var h=Date.now||function(){return+new Date};function k(a,b){function c(){}c.prototype=b.prototype;a.prototype=new c;a.prototype.constructor=a};function l(a){l[" "](a);return a}l[" "]=function(){};function m(){}var n="function"==typeof Uint8Array;function p(a,b,c){a.b=null;b||(b=[]);a.i=void 0;a.f=-1;a.a=b;a:{if(b=a.a.length){--b;var d=a.a[b];if(!(null===d||"object"!=typeof d||Array.isArray(d)||n&&d instanceof Uint8Array)){a.g=b-a.f;a.c=d;break a}}a.g=Number.MAX_VALUE}a.h={};if(c)for(b=0;b<c.length;b++)if(d=c[b],d<a.g)d+=a.f,a.a[d]=a.a[d]||q;else{var f=a.g+a.f;a.a[f]||(a.c=a.a[f]={});a.c[d]=a.c[d]||q}}var q=[];
function r(a,b){if(b<a.g){b+=a.f;var c=a.a[b];return c===q?a.a[b]=[]:c}if(a.c)return c=a.c[b],c===q?a.c[b]=[]:c}function t(a){a=r(a,2);return null==a?0:a}function u(a){a=r(a,16);a=null==a?a:!!a;return null==a?!1:a}function v(a,b,c){a.b||(a.b={});if(!a.b[c]){var d=r(a,c);d&&(a.b[c]=new b(d))}return a.b[c]}function w(a){if(a.b)for(var b in a.b){var c=a.b[b];if("array"==g(c))for(var d=0;d<c.length;d++)c[d]&&w(c[d]);else c&&w(c)}}m.prototype.toString=function(){w(this);return this.a.toString()};function x(a){p(this,a,y)}k(x,m);var y=[17];function z(a){p(this,a,A)}k(z,m);var A=[27];function B(a){p(this,a,C)}k(B,m);var C=[8];var D=document;function E(){var a=F;try{var b;if(b=!!a&&null!=a.location.href)a:{try{l(a.foo);b=!0;break a}catch(c){}b=!1}return b}catch(c){return!1}};/*
 Copyright (c) Microsoft Corporation. All rights reserved.
 Licensed under the Apache License, Version 2.0 (the "License"); you may not use
 this file except in compliance with the License. You may obtain a copy of the
 License at http://www.apache.org/licenses/LICENSE-2.0

 THIS CODE IS PROVIDED ON AN *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
 WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
 MERCHANTABLITY OR NON-INFRINGEMENT.

 See the Apache Version 2.0 License for specific language governing permissions
 and limitations under the License.
*/
var G=!!window.google_async_iframe_id;let F=G&&window.parent||window;let H=null;class J{constructor(a,b,c,d=0,f){this.label=a;this.type=b;this.value=c;this.duration=d;this.uniqueId=Math.random();this.slotId=f}};const K=e.performance,L=!!(K&&K.mark&&K.measure&&K.clearMarks),M=function(a){let b=!1,c;return function(){b||(c=a(),b=!0);return c}}(()=>{var a;if(a=L){var b;if(null===H){H="";try{a="";try{a=e.top.location.hash}catch(c){a=e.location.hash}a&&(H=(b=a.match(/\bdeid=([\d,]+)/))?b[1]:"")}catch(c){}}b=H;a=!!b.indexOf&&0<=b.indexOf("1337")}return a});function N(a){a&&K&&M()&&(K.clearMarks(`goog_${a.label}_${a.uniqueId}_start`),K.clearMarks(`goog_${a.label}_${a.uniqueId}_end`))}
class O{constructor(a,b){this.a=[];this.c=b||e;let c=null;b&&(b.google_js_reporting_queue=b.google_js_reporting_queue||[],this.a=b.google_js_reporting_queue,c=b.google_measure_js_timing);this.b=M()||(null!=c?c:Math.random()<a)}start(a,b){if(!this.b)return null;var c=(c=e.performance)&&c.now?c.now():null;c||(c=(c=e.performance)&&c.now&&c.timing?Math.floor(c.now()+c.timing.navigationStart):h());a=new J(a,b,c);b=`goog_${a.label}_${a.uniqueId}_start`;K&&M()&&K.mark(b);return a}};if(G&&!E()){let a="."+D.domain;try{for(;2<a.split(".").length&&!E();)D.domain=a=a.substr(a.indexOf(".")+1),F=window.parent}catch(b){}E()||(F=window)}const P=F,Q=new O(1,P);var R=()=>{P.google_measure_js_timing||(Q.b=!1,Q.a!=Q.c.google_js_reporting_queue&&(M()&&Array.prototype.forEach.call(Q.a,N,void 0),Q.a.length=0))};"number"!==typeof P.google_srt&&(P.google_srt=Math.random());if("complete"==P.document.readyState)R();else if(Q.b){var S=()=>{R()};P.addEventListener&&P.addEventListener("load",S,!1)};var T=class{constructor(){}};function U(a,b){a=a.getElementsByTagName("META");for(let c=0;c<a.length;++c)if(a[c].getAttribute("name")===b)return a[c].getAttribute("content");return""};class V{constructor(a,b){this.a=b;a=U(b,"namespace");if(!a){a="ns-"+Math.random().toString(36).substr(2,5);a:{var c=b.getElementsByTagName("META");for(let d=0;d<c.length;++d)if("namespace"===c[d].getAttribute("name")){c[d].setAttribute("content",a);break a}c=b.querySelector("#mys-meta");c||(c=document.createElement("div"),c.id="mys-meta",c.style.position="absolute",c.style.display="none",b.appendChild(c));b=document.createElement("META");b.setAttribute("name","namespace");b.setAttribute("content",
a);c.appendChild(b)}}}dispatchEvent(a,b){a=null==b?new CustomEvent(a):new CustomEvent(a,{detail:b});this.a.dispatchEvent(a)}addEventListener(a,b){this.a.addEventListener(a,b)}};class W{constructor(){this.a={}}set(a,b){this.a[a]=b}get(a){return this.a[a]}};class aa extends T{constructor(a){super();this.context=a;this.a=new W}};function ba(a){var b=X;2==t(b)||v(v(b,z,1),x,10)&&u(v(v(b,z,1),x,10))||(b=0,mys.engine&&(b=mys.engine.stage()),0==(b&1)&&a.a.addEventListener("overallStart",()=>{}),a.a.addEventListener("browserStart",()=>{}),a.a.addEventListener("browserReady",()=>{}),a.a.addEventListener("browserQuiet",()=>{}))}class ca{constructor(a,b){this.b=a;this.a=b}};var da=class extends aa{constructor(a){super(a)}};var ea=class extends da{};class fa extends ea{};{var ha=b=>new fa(b);const a=document.getElementById("mys-content");if(a){const b=new V(document.head,a),c=ha(b),d=new ca(c,b);var ia=d.b.a,Y=U(b.a,"runtime_data");if(Y){const f=JSON.parse(Y);for(const I in f)ia.set(I,f[I])}var X,Z=U(b.a,"render_config")||"[]";X=new B(Z?JSON.parse(Z):null);ba(d)}};}).call(this);
