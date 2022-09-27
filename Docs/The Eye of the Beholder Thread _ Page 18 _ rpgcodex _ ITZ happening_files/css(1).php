@charset "UTF-8";

/* --- bb_code.css --- */

.quoteContainer.expanded iframe[data-s9e-mediaembed],
	.quoteContainer.expanded [data-s9e-mediaembed] iframe
	{
		max-height: none;
		max-width:  none;
	}/* .bbCodeX classes are designed to exist inside .baseHtml. ie: they have no CSS reset applied */

.bbCodeBlock
{
	margin: 0 5em 1em;

}

	.bbCodeBlock .bbCodeBlock,
	.hasJs .bbCodeBlock .bbCodeSpoilerText,
	.messageList.withSidebar .bbCodeBlock
	{
		margin-right: 0;
	}

	/* mini CSS reset */
	.bbCodeBlock pre,
	.bbCodeBlock blockquote
	{
		margin: 0;
	}
	
	.bbCodeBlock img
	{
		border: none;
	}

.bbCodeBlock .type
{
	font-size: 11px;
font-family: Tahoma, Verdana, Arial, Helvetica, sans-serif;
color: ;
padding: 3px 8px;

}

.bbCodeBlock pre,
.bbCodeBlock .code
{
	font-size: 11px;
font-family: Consolas, 'Courier New', Courier, monospace;
background-color: #353F55;
padding: 5px;
border: 1px solid #3F3F3F;
word-wrap: normal;
overflow: auto;
line-height: 1.24;
min-height: 30px;
max-height: 500px;
_width: 600px;
direction: ltr;

}

.bbCodeBlock .code
{
	white-space: nowrap;
}

.bbCodeQuote
{
	
}

.bbCodeQuote .attribution
{
	
}

.bbCodeQuote .quoteContainer
{
	overflow: hidden;
	position: relative;
	
	font-size: 12px;
background-color: #353F55;
padding: 5px;
border: 1px solid #3F3F3F;

}


	.bbCodeQuote .quoteContainer .quoteExpand
	{
		display: none;
	}


	.bbCodeQuote img
	{
		max-height: 150px;
	}
	
	.bbCodeQuote iframe, .bbCodeQuote [data-s9e-mediaembed],
	.bbCodeQuote object,
	.bbCodeQuote embed
	{
		max-width: none; /* 200px */
		max-height: none; /* 150px */
	}
	
	.bbCodeQuote iframe:-webkit-full-screen
	{
		max-width: none;
		max-height: none;
	}
	
	.bbCodeQuote iframe:-moz-full-screen
	{
		max-width: none;
		max-height: none;
	}
	
	.bbCodeQuote iframe:-ms-fullscreen
	{
		max-width: none;
		max-height: none;
	}
	
	.bbCodeQuote iframe:fullscreen
	{
		max-width: none;
		max-height: none;
	}
	
.bbCodeSpoilerButton
{
	margin: 5px 0;
	max-width: 99%;
}

	.bbCodeSpoilerButton > span
	{
		display: inline-block;
		max-width: 100%;
		white-space: nowrap;
		text-overflow: ellipsis;
		overflow: hidden;
	}
	
.hasJs .bbCodeSpoilerText
{
	display: none;
	background-color: ;
padding: 5px;
margin-top: 5px;
margin-right: 149px;
margin-bottom: 5px;
border: 1px solid ;
border-radius: 5px;
overflow: auto;

}

	.hasJs .bbCodeSpoilerText .bbCodeSpoilerText,
	.hasJs .bbCodeSpoilerText .bbCodeBlock,
	.hasJs .messageList.withSidebar .bbCodeSpoilerText
	{
		margin-right: 0;
	}
	
.NoJs .bbCodeSpoilerContainer
{
	background-color: ; /* fallback for browsers without currentColor */
	background-color: currentColor;
}

	.NoJs .bbCodeSpoilerContainer > .bbCodeSpoilerText
	{
		visibility: hidden;
	}

	.NoJs .bbCodeSpoilerContainer:hover
	{
		background-color: transparent;
	}
	
		.NoJs .bbCodeSpoilerContainer:hover > .bbCodeSpoilerText
		{
			visibility: visible;
		}


@media (max-width:800px)
{
	.Responsive .bbCodeBlock,
	.Responsive.hasJs .bbCodeSpoilerText
	{
		margin-right: 0;
	}
}


/* --- bbm_buttons.css --- */

span.mce_bbm_hl {background-position:-760px 0 !important}
span.mce_bbm_raw {background-position:-260px 0 !important}
span.mce_bbm_spoiler {
	background:url(styles/sedo/editor/adv_sprites.png) no-repeat 0 0 !important;
}

/* --- cz_dice.css --- */

/* die */

.dice_container, .listr_container
{
	margin: 10px;
	padding: 10px;
	border: #000 1px solid;
	width: 400px;
}

.moreOptionsLink
{
	display: inline;
	width: 100px;
	margin-left: 10px;
}

.dice_container legend, .listr_container legend
{
	color: ;
}

fieldset.dice_container, fieldset.listr_container
{
	border-color: ;
}


.listr_container li
{
	margin-left: 15px;
}

.listr_container .selection
{
	margin-top: 10px;
}


/* list data */

#pickListOptions
{
	overflow-y: auto;
	height: 200px;
}





/* --- dark_postrating.css --- */

.dark_postrating { margin-top: 10px; margin-left: 149px  } 
.primaryContent > .dark_postrating { margin-left: 0; padding-bottom: 6px; }
.messageSimple .dark_postrating { background: transparent; border-bottom: none; margin-left: 65px; margin-top: 6px !important; border-top: 1px solid ; }

.dark_postrating_table { border-spacing: 5px; border-collapse: separate; }
.dark_postrating_detail { background: ; font-family: 'Trebuchet MS',Helvetica,Arial,sans-serif; color:; font-size: 11px; padding: 4px !important; }
.dark_postrating_column { vertical-align: top; padding: 0; margin: 3px; width: 155px; border: 1px solid ; }
.dark_postrating_column > div { display: block; max-height: 105px; overflow: auto; padding: 7px; }
.dark_postrating_delete { display: block; visibility: hidden; float: left; height: 13px; margin-right: 3px; width: 12px; color: #FF239E; background: url(styles/dark/cross_small.png) center no-repeat; }
.dark_postrating_column:hover .dark_postrating_moderator { visibility: visible !important; }
.dark_postrating_header strong { font-weight: bold; color:;  }
.dark_postrating_header img { vertical-align: middle; position: relative; top: -2px; }
.dark_postrating_header { font-size: 14px; margin-bottom: 2px; padding-bottom: 3px; border-bottom: 1px dotted ; }
.dark_postrating_column a.username { display: block; /*float: left; clear: left;*/ }
/*.dark_postrating_delete + a.username { width: 125px; }*/

.dark_postrating_member { background: #48505F; border: 2px solid black; color: ; width: 100%; padding: 5px 25px; }
.dark_postrating_member td, .dark_postrating_member th { padding: 2px 4px 1px; text-align: center; }
.dark_postrating_member td { border-width: 1px 0px 0 0; border-style: solid; border-color: ; }
.dark_postrating_member tr:nth-child(2) td { border-width: 0; }
.dark_postrating_member th { color: ; font-size: 11px; }
.dark_postrating_member img { vertical-align: text-top; }
.dark_postrating_positive { color: #62A201; }
.dark_postrating_negative { color: #D90B00; }
.dark_postrating_bar { width: 80px; height: 10px; background: transparent; border: 1px solid #ddd; border-radius: 2px; padding: 1px; font-size: 0; }
.dark_postrating_bar_positive { height: 10px; background: #62A201; display: inline-block; opacity: 0.4; font-size: 0; }
.dark_postrating_bar_neutral { height: 10px; background: #bbb; display: inline-block; opacity: 0.4; font-size: 0; }
.dark_postrating_bar_negative { height: 10px; background: #D90B00; display: inline-block; opacity: 0.4; font-size: 0; }
.dark_postrating_bar:hover > div { opacity: 1.0; }
.profilePage .infoBlock dd.dark_postrating_bar_dd:last-child { margin-bottom: 0; }

.dark_postrating_inputlist { display: block; cursor: default; float: right; opacity: 1.0; font-size: 11px; min-height: 22px; -ms-filter:'alpha(opacity=100)'; filter:alpha(opacity=100) }
.dark_postrating_inputlist.dark_postrating_inputlist_undo li { opacity: 1.0; -ms-filter:'alpha(opacity=100)'; filter:alpha(opacity=100) }
.dark_postrating_inputlist li { display: inline; opacity: 0.5; -ms-filter:'alpha(opacity=50)'; filter:alpha(opacity=50); zoom:1; }
.dark_postrating_ie8 .dark_postrating_inputlist li { display: inline-block }
.dark_postrating_inputlist li:hover { opacity: 1.0; -ms-filter:'alpha(opacity=100)'; filter:alpha(opacity=100) }
li.dark_postrating_textonly { vertical-align: top; display: inline-block; margin: 1px 4px 0 4px; }

.dark_postrating_outputlist { display: block; margin-left: 3px; float: left; font-family: 'Trebuchet MS',Helvetica,Arial,sans-serif; color:; font-size: 11px;}
.dark_postrating_outputlist li { display: inline; margin-right: 6px; }
.dark_postrating_outputlist li strong { font-weight: bold; color:;  }
.dark_postrating_outputlist li img { vertical-align: text-top; }

.dark_postrating_hide_post { display: none }
.message > .dark_postrating_hide_post { display: block !important }

/* --- login_bar.css --- */

/** Login bar basics **/

#loginBar
{
	color: white;
background-color: #48505F;
border-bottom: 1px solid #032A46;
position: relative;
z-index: 1;

}

	#loginBar .ctrlWrapper
	{
		margin: 0 10px;
	}

	#loginBar .pageContent
	{
		padding-top: 5px;
		position: relative;
		_height: 0px;
	}

	#loginBar a
	{
		color: ;

	}

	#loginBar form
	{
		padding: 5px 0;
margin: 0 auto;
display: none;
line-height: 20px;
position: relative;

	}
	
		#loginBar .xenForm .ctrlUnit,		
		#loginBar .xenForm .ctrlUnit > dt label
		{
			margin: 0;
			border: none;
		}
	
		#loginBar .xenForm .ctrlUnit > dd
		{
			position: relative;
		}
	
	#loginBar .lostPassword,
	#loginBar .lostPasswordLogin
	{
		font-size: 11px;
	}
	
	#loginBar .rememberPassword
	{
		font-size: 11px;
	}

	#loginBar .textCtrl
	{
		color: white;
background-color: #3F3F3F;
border: 1px solid white;

	}
	
	#loginBar .textCtrl[type=text]
	{
		font-weight: bold;
font-size: 18px;

	}

	#loginBar .textCtrl:-webkit-autofill /* http://code.google.com/p/chromium/issues/detail?id=1334#c35 */
	{
		background: #3F3F3F !important;
		color: white;
	}

	#loginBar .textCtrl:focus
	{
		background-color: #C12A2A;

	}
	
	#loginBar input.textCtrl.disabled
	{
		color: ;
background-color: rgb(53, 63, 85);
border-style: dashed;

	}
	
	#loginBar .button
	{
		min-width: 85px;
		*width: 85px;
	}
	
		#loginBar .button.primary
		{
			font-weight: bold;
		}
		
/** changes when eAuth is present **/

#loginBar form.eAuth
{
	-x-max-width: 700px; /* normal width + 170px */
}

	#loginBar form.eAuth .ctrlWrapper
	{
		border-right: 1px dotted ;
		margin-right: 200px;
		box-sizing: border-box;
	}

	#loginBar form.eAuth #eAuthUnit
	{
		position: absolute;
		top: 0px;
		right: 10px;
	}

		#eAuthUnit li
		{
			margin-top: 10px;
			line-height: 0;
		}
	
/** handle **/

#loginBar #loginBarHandle
{
	font-size: 11px;
color: white;
background-color: #48505F;
padding: 0 10px;
margin-right: 20px;
border-bottom-right-radius: 10px;
border-bottom-left-radius: 10px;
position: absolute;
right: 0px;
bottom: -20px;
text-align: center;
z-index: 1;
line-height: 20px;
box-shadow: 0px 2px 5px #596170;

}


@media (max-width:800px)
{
	.Responsive #loginBar form.eAuth .ctrlWrapper
	{
		border-right: none;
		margin-right: 10px;
	}

	.Responsive #loginBar form.eAuth #eAuthUnit
	{
		position: static;
		width: 180px;
		margin: 0 auto 10px;
	}
}


/* --- message.css --- */



.messageList
{
	background-color: #3F3F3F;
padding: 2px;
border: 2px solid black;

}

.messageList .message
{
	background-color: #48505F;
padding: 0px;
border: 1px solid #3F3F3F;
border-top: 4px solid #3F3F3F;
border-bottom: 10px solid #353F55;

}

/* clearfix */ .messageList .message { zoom: 1; } .messageList .message:after { content: '.'; display: block; height: 0; clear: both; visibility: hidden; }

/*** Message block ***/

.message .messageInfo
{
	padding: 5px;
margin-left: 149px;
border-bottom: 1px none black;
border-left: 1px solid #3F3F3F;

	zoom: 1;
}

	.message .newIndicator
	{
		font-size: 11px;
color: ;
background-color: #992222;
padding: 1px 5px;
margin: -5px -5px 5px 5px;
border: 1px solid black;
border-radius: 3px;
border-top-right-radius: 0px;
display: block;
float: right;
position: relative;
box-shadow: 1px 1px 3px rgba(0,0,0, 0.25);

		
		margin-right: -25px;
	}
	
		.message .newIndicator span
		{
			background-color: ;
border-top-right-radius: 3px;
position: absolute;
top: -4px;
right: -1px;
width: 5px;
height: 4px;

		}

	.message .messageContent
	{
		padding-bottom: 5px;
min-height: 100px;

	}
	
	.message .messageTextEndMarker
	{
		height: 0;
		font-size: 0;
		overflow: hidden;
	}
	
	.message .editDate
	{
		text-align: right;
		margin-top: 5px;
		font-size: 11px;
		color: ;
	}

	.message .signature
	{
		font-size: 12px;
padding: 5px 0;
margin: 0px;
border-top: 1px solid #B3B3B3;
max-height: 124px;
overflow: hidden !important;

	}

	.message .messageMeta
	{
		font-size: 11px;
padding: 0 0 5px;
margin-top: 0px;
border-bottom: 1px solid #353F55;
overflow: hidden;
zoom: 1;

	}

		.message .privateControls
		{
			padding: 0px;
float: left;

		}

		.message .publicControls
		{
			float: right;

		}
		
			.message .privateControls .item
			{
				margin-right: 10px;
				float: left;
			}

				.message .privateControls .item:last-child
				{
					margin-right: 0;
				}

			.message .publicControls .item
			{
				margin-left: 10px;
				float: left;
			}
	
				.message .messageMeta .control
				{
					
				}
				
					.message .messageMeta .control:focus
					{
						
					}
				
					.message .messageMeta .control:hover
					{
						
					}
				
					.message .messageMeta .control:active
					{
						
					}
	/*** multiquote +/- ***/
			
	.message .publicControls .MultiQuoteControl
	{
		padding-left: 4px;
		padding-right: 4px;
		border-radius: 2px;
		margin-left: 6px;
		margin-right: -4px;
	}
	
	
	.message .publicControls .MultiQuoteControl.active
	{
		background-color: ;
	}
	
		.messageNotices li
	{
		font-size: 11px;
background-color: #596170;
padding: 5px;
margin: 10px 0;
border: 1px solid ;
border-radius: 5px;
line-height: 16px;

	}
	
		.messageNotices .icon
		{
			float: right;
			width: 16px;
			height: 16px;
			background: url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat 1000px 1000px;
		}
	
			.messageNotices .warningNotice .icon { background-position: -48px -32px; }		
			.messageNotices .deletedNotice .icon { background-position: -64px -32px; }		
			.messageNotices .moderatedNotice .icon {background-position: -32px -16px; }
	
	.message .likesSummary
	{
		padding: 5px;
margin-top: 10px;
border: 1px solid #B3B3B3;
border-radius: 5px;

	}
	
	.message .messageText > *:first-child
	{
		margin-top: 0;
	}

/* inline moderation changes */

.InlineModChecked .messageUserBlock,
.InlineModChecked .messageInfo,
.InlineModChecked .messageNotices,
.InlineModChecked .bbCodeBlock .type,
.InlineModChecked .bbCodeBlock blockquote,
.InlineModChecked .attachedFiles .attachedFilesHeader,
.InlineModChecked .attachedFiles .attachmentList
{
	background-color: #992222;
overflow: hidden;

}

.InlineModChecked .messageUserBlock div.avatarHolder,
.InlineModChecked .messageUserBlock .extraUserInfo
{
	background: transparent;
}

.InlineModChecked .messageUserBlock .arrow span
{
	border-left-color: ;
}

/* message list */

.messageList .newMessagesNotice
{
	margin: 10px auto;
	padding: 5px 10px;
	border-radius: 5px;
	border: 1px solid ;
	background:  url(styles/default/xenforo/gradients/category-23px-light.png) repeat-x top;
	font-size: 11px;
}

/* deleted / ignored message placeholder */

.messageList .message.placeholder
{
}

.messageList .placeholder .placeholderContent
{	
	overflow: hidden; zoom: 1;
	color: rgb(179, 179, 179);
	font-size: 11px;
}

	.messageList .placeholder a.avatar
	{
		float: left;
		display: block;
	}
	
		.messageList .placeholder a.avatar img
		{
			display: block;
			width: 32px;
			height: 32px;
		}
		
	.messageList .placeholder .privateControls
	{
		margin-top: -5px;
	}
	

/* messages remaining link */

.postsRemaining a,
a.postsRemaining
{
	font-size: 11px;
	color: ;
}


@media (max-width:800px)
{
	.Responsive .message .newIndicator
	{
		margin-right: 0;
		border-top-right-radius: 3px;
	}
	
		.Responsive .message .newIndicator span
		{
			display: none;
		}
}

@media (max-width:480px)
{
	.Responsive .message .messageInfo
	{
		margin-left: 0;
		padding: 0 10px;
	}

	.Responsive .message .messageContent
	{
		min-height: 0;
	}	

	.Responsive .message .newIndicator
	{
		margin-right: -5px;
		margin-top: -16px;
	}

	.Responsive .message .postNumber,
	.Responsive .message .authorEnd
	{
		display: none;
	}
	
	.Responsive .message .signature
	{
		display: none;
	}
	
	.Responsive .messageList .placeholder a.avatar
	{
		margin-right: 10px;
	}
}


/* --- message_user_info.css --- */

.messageUserInfo
{
	float: left;
width: 150px;

}

	.messageUserBlock
	{
		border-right: 1px solid #3F3F3F;

		
		position: relative;
	}
		
		.messageUserBlock div.avatarHolder
		{
			padding: 0 0 0 5px;
border: 1px none black;

			
			position: relative;	
		}
		
			.messageUserBlock div.avatarHolder .avatar
			{
				display: block;
				font-size: 0;
			}
			
			.messageUserBlock div.avatarHolder .onlineMarker
			{
				position: absolute;
				top: -1px;
				left: -1px;
				
				border: 7px solid transparent;
border-top-color: rgb(127, 185, 0);
border-left-color: rgb(127, 185, 0);
border-top-left-radius: 5px;
border-top-right-radius: 3px;
border-bottom-left-radius: 3px;

			}
			
		.messageUserBlock h3.userText
		{
			padding: 6px;

		}
		
		.messageUserBlock .userBanner
		{
			display: block;
			margin-bottom: 5px;
			margin-left: -12px;
			margin-right: -12px;
		}
		
		.messageUserBlock .userBanner:last-child
		{
			margin-bottom: 0;
		}
	
		.messageUserBlock a.username
		{
			font-weight: bold;
display: block;
overflow: hidden;
line-height: 16px;

			
		}
		
		.messageUserBlock .userTitle
		{
			font-size: 11px;
display: block;

		}
		
		.messageUserBlock .extraUserInfo
		{
			font-size: 11px;
background-color: ;
padding: 4px 6px;
border-radius: 4px;

		}
		
			.messageUserBlock .extraUserInfo dl
			{
				margin: 2px 0 0;
			}
							
			.messageUserBlock .extraUserInfo img
			{
				max-width: 100%;
			}
		
		.messageUserBlock .arrow
		{
			position: absolute;
			top: 10px;
			right: -10px;
			
			display: block;
			width: 0px;
			height: 0px;
			line-height: 0px;
			
			border: 10px solid transparent;
			border-left-color: ;
			-moz-border-left-colors: ;
			border-right: none;
			
			/* Hide from IE6 */
			_display: none;
		}
		
			.messageUserBlock .arrow span
			{
				position: absolute;
				top: -10px;
				left: -11px;
				
				display: block;
				width: 0px;
				height: 0px;
				line-height: 0px;
				
				border: 10px solid transparent;
				border-left-color: ;
				-moz-border-left-colors: ;
				border-right: none;
			}


@media (max-width:480px)
{
	.Responsive .messageUserInfo
	{
		float: none;
		width: auto; 
	}

	.Responsive .messageUserBlock
	{
		overflow: hidden;
		margin-bottom: 5px;
		position: relative;
	}

	.Responsive .messageUserBlock div.avatarHolder
	{
		float: left;
		padding: 5px;
	}

		.Responsive .messageUserBlock div.avatarHolder .avatar img
		{
			width: 48px;
			height: 48px;
		}
		
		.Responsive .messageUserBlock div.avatarHolder .onlineMarker
		{
			top: 4px;
			left: 4px;
			border-width: 6px;
		}

	.Responsive .messageUserBlock h3.userText
	{
		margin-left: 64px;
	}
	
	.Responsive .messageUserBlock .userBanner
	{
		max-width: 150px;
		margin-left: 0;
		margin-right: 0;
		border-top-left-radius: 3px;
		border-top-right-radius: 3px;
		position: static;
		display: inline-block;
	}
	
		.Responsive .messageUserBlock .userBanner span
		{
			display: none;
		}

	.Responsive .messageUserBlock .extraUserInfo
	{
		display: none;
	}

	.Responsive .messageUserBlock .arrow
	{
		display: none;
	}
}


/* --- notices.css --- */

.hasJs .FloatingContainer .Notice
{
	display: none;
}

.FloatingContainer
{
	position: fixed;
	width: 300px;
	z-index: 9997;
	top: auto;
	left: auto;
	bottom: 0;
	right: 20px;
}

.Notices .Notice .blockImage
{
	padding: 10px 0 5px 10px;
}

.Notices .Notice .blockImage,
.FloatingContainer .floatingImage
{
	float: left;
}

.Notices .Notice .blockImage img,
.FloatingContainer .floatingImage img
{
	max-width: 48px;
	max-height: 48px;
}

.Notices .hasImage,
.FloatingContainer .hasImage
{
	margin-left: 64px;
	min-height: 52px;
}

.FloatingContainer .floatingItem
{
	display: block;
	padding: 10px;
	font-size: 11px;
	position: relative;
	margin-bottom: 20px;
	border: 1px solid transparent;
	border-radius: 6px;
	box-shadow: 1px 1px 3px rgba(0,0,0, 0.25);
}

.FloatingContainer .floatingItem.primary
{
	background-color: #48505F;
	border-color: ;
}

.FloatingContainer .floatingItem.secondary
{
	color: ;
	background-color: ;
	border-color: ;
}

.FloatingContainer .floatingItem.dark
{
	color: #fff;
	background: black;
	background: url(rgba.php?r=0&g=0&b=0&a=204); background: rgba(0,0,0, 0.8); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#CC000000,endColorstr=#CC000000);
	border-color: #333;
}

.FloatingContainer .floatingItem.light
{
	color: #000;
	background: white;
	background: url(rgba.php?r=255&g=255&b=255&a=204); background: rgba(255,255,255, 0.8); _filter: progid:DXImageTransform.Microsoft.gradient(startColorstr=#CCFFFFFF,endColorstr=#CCFFFFFF);
	border-color: #ddd;
}

.FloatingContainer .floatingItem .title
{
	font-size: 14px;
	padding-bottom: 5px;
	font-weight: bold;
	display: block;
}

.FloatingContainer .floatingItem .DismissCtrl
{
	position: static;
	float: right;
	margin-left: 5px;
	margin-right: -5px;
	margin-top: -5px;
}

.Notices
{
	display: none;
}

/* cookie notice */
.Notice.notice_-1 .noticeCookiesContent .noticeCookiesContentRow
{
	text-align: center;
}

.Notice.notice_-1 .noticeCookiesContent .noticeCookiesContentRow.noticeCookiesContentButtonRow
{
	margin-top: 10px;
}


	@media (max-width:800px)
	{
		.Responsive .Notice.wide { display: none !important; }

		/* cookie notice */
		.Responsive .Notice.notice_-1 .noticeContent
		{
			padding: 3px 3px 10px 3px;
		}

		.Responsive .Notice.notice_-1 .noticeCookiesContent .noticeCookiesContentRow
		{
			font-size: 12px;
		}

		.Responsive .Notice.notice_-1 .noticeCookiesContent .noticeCookiesContentRow.noticeCookiesContentButtonRow .button
		{
			font-size: 11px;
			padding: 0px 4px;
			border-radius: 5px;
		}
	}
	
	@media (max-width:610px)
	{
		.Responsive .Notice.medium { display: none !important; }
	}
	
	@media (max-width:480px)
	{
		.Responsive .Notice.narrow { display: none !important; }
		
		.Responsive .FloatingContainer
		{
			right: 50%;
			margin-right: -150px;
		}
	}


/* --- panel_scroller.css --- */

.hasJs .Notices.PanelScroller { display: none; }

.PanelScroller .scrollContainer,
.PanelScrollerOff .panel
{
	background-color: #48505F;
padding: 3px;
margin-bottom: 10px;
border: 1px solid ;
border-radius: 5px;
font-size: 12px;

}

.PanelScroller .PanelContainer
{
	position: relative;
	clear: both;
	width: 100%;
	overflow: auto;
}

	.hasJs .PanelScroller .Panels
	{
		position: absolute;
	}

	.PanelScroller .Panels
	{
		clear: both;
		margin: 0;
		padding: 0;
	}
	
		.PanelScroller .panel,
		.PanelScrollerOff .panel
		{
			overflow: hidden;
			position: relative;
			padding: 0 !important;

			padding: 10px;

		}
			
		.PanelScroller .panel .noticeContent,
		.PanelScrollerOff .panel .noticeContent
		{
			padding: 10px;
		}

/** panel scroller nav **/

.PanelScroller .navContainer
{
	margin: -11px 21px 10px;
overflow: hidden;
zoom: 1;

}

.PanelScroller .navControls
{
	float: right;
}

/* clearfix */ .PanelScroller .navControls { zoom: 1; } .PanelScroller .navControls:after { content: '.'; display: block; height: 0; clear: both; visibility: hidden; }

	.PanelScroller .navControls a
	{
		font-size: 9px;
background-color: ;
padding: 3px 6px 2px;
margin-left: -1px;
float: left;
display: block;
position: relative;

		
		border: 1px solid ;
border-radius: 5px;
		border-radius: 0;
	}
	
		.PanelScroller .navControls > a:first-child
		{
			border-bottom-left-radius: 5px;
		}
		
		.PanelScroller .navControls > a:last-child
		{
			border-bottom-right-radius: 5px;
		}
		
		.PanelScroller .navControls a:hover
		{
			text-decoration: none;
background-color: ;

		}
		
		.PanelScroller .navControls a.current
		{
			background-color: ;

		}
		
			.PanelScroller .navControls a .arrow
			{
				display: none;
			}
			
			.PanelScroller .navControls a.current span
			{
				display: block;
				line-height: 0px;
				width: 0px;
				height: 0px;
				border-top: 5px solid ;
				border-right: 5px solid transparent;
				border-bottom: 1px none black;
				border-left: 5px solid transparent;
				-moz-border-bottom-colors: ;
				position: absolute;
			}
			
			.PanelScroller .navControls a.current .arrow
			{
				border-top-color: ;
				top: 0px;
				left: 50%;
				margin-left: -5px;
			}
			
				.PanelScroller .navControls a .arrow span
				{
					border-top-color: #48505F;
					top: -6px;
					left: -5px;
				}
				
/* notices */

.Notices .panel .noticeContent
{
	padding-right: 25px;
}

.bottomFixer .PanelScroller .panel,
.bottomFixer .PanelScrollerOff .panel
{
	margin-bottom: 0;
	border-radius: 0;
}

/* --- thread_view.css --- */

.thread_view .threadAlerts
{
	border: 1px solid ;
	border-radius: 5px;
	font-size: 11px;
	margin: 10px 0;
	padding: 5px;
	line-height: 16px;
	background-image: url('styles/default/xenforo/gradients/form-button-white-25px.png');
}
	
	.thread_view .threadAlerts dt
	{
		color: ;
		display: inline;
	}
	
	.thread_view .threadAlerts dd
	{
		color: ;
		font-weight: bold;
		display: inline;
	}
	
		.thread_view .threadAlerts .icon
		{
			float: right;
			width: 16px;
			height: 16px;
			margin-left: 5px;
			background: url('styles/default/xenforo/xenforo-ui-sprite.png') no-repeat -1000px -1000px;
		}
		
			.thread_view .threadAlerts .deletedAlert .icon { background-position: -64px -32px; }
			.thread_view .threadAlerts .moderatedAlert .icon { background-position: -32px -16px; }
			.thread_view .threadAlerts .lockedAlert .icon { background-position: -16px -16px; }
	
.thread_view .threadAlerts + * > .messageList
{
	border-top: none;
}

.thread_view .threadNotices
{
	background-color: ;
	border: 1px solid ;
	border-radius: 5px;
	padding: 10px;
	margin: 10px auto;
}

.thread_view .InlineMod
{
	overflow: hidden; zoom: 1;
}

#QuoteSelected .ReplyQuote:last-child
{
	display: none;
}
