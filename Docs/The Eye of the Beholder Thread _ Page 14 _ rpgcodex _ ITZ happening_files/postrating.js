$(document).ready(function(){

	if($.browser.msie && parseInt($.browser.version) == 8)
		$("body").addClass("dark_postrating_ie8");
	
	// if mobile don't fade input
	if(XenForo.isTouchBrowser()){
		$("ul.dark_postrating_inputlist").css({opacity:"1.0"});
	} else {
		$("li.message, li.messageSimple").live({
			mouseenter: function(e){
				var $inputList = $(this).find("ul.dark_postrating_inputlist");
				if($inputList.length > 0)
					$inputList.stop().animate({opacity: "1.0"}, 200);
			}, 
			mouseleave: function(e){
				var $inputList = $(this).find("ul.dark_postrating_inputlist");
				if($inputList.length > 0)
					$inputList.stop().animate({opacity: dark_postrating_minimum_opacity}, 200);
			}
		});
		$("ul.dark_postrating_inputlist").css({opacity: dark_postrating_minimum_opacity});
	}
		
	$("ul.dark_postrating_inputlist a").live('click', function(e){
		e.preventDefault();
		var $link = $(this);
		$(".xenTooltip").hide();

		XenForo.ajax(this.href.replace(/(&_xfToken=.*)/, ''), {}, function(ajaxData, textStatus){
			
			$(".xenTooltip").hide();
		
			if (XenForo.hasResponseError(ajaxData)){
				return false;
			}
			
			if(ajaxData.templateHtml == 'lock'){
				// try again
				$link.click();
				return false;
			}
			
			var $containerOut    = $link.parents(".dark_postrating_container"),
				$templateHtml    = $(ajaxData.templateHtml);
						
			$templateHtml.find(".dark_postrating_inputlist .Tooltip").data("offsetX", "-24");
			
			$containerOut.xfFadeOut(50, function()
			{				
				$(".xenTooltip").hide();
				if($containerOut.parent().length == 0)
					return false;
				$containerOut.parent().get(0).className = $templateHtml.get(0).className;
				// since everything else is getting destroyed, jump up a bit...
				$container = $containerOut.parent();
				$templateHtml.find('.dark_postrating_container').xfInsert('replaceAll', $containerOut, 'xfFadeIn', 50);
				$container.find('.dark_postrating_inputlist').stop().css({opacity:"1.0"});
			});
			
		});
	});	
	
	$(".dark_postrating_moderator").live('click', function(e){
		e.preventDefault();
		var $link = $(this);

		XenForo.ajax(this.href.replace(/(&_xfToken=.*)/, ''), {}, function(ajaxData, textStatus){
					
			if (XenForo.hasResponseError(ajaxData)){
				return false;
			}
			
			var $containerOut    = $("#post-"+$link.data("post")).find(".dark_postrating_container"),
				$templateHtml    = $(ajaxData.templateHtml);
				
			if($link.siblings(":visible").length <= 2){
				$link.parents(".dark_postrating_column").fadeOut(500);
			}
			$link.next().fadeOut(500);
			$link.fadeOut(500);
			
			$templateHtml.find(".dark_postrating_inputlist .Tooltip").data("offsetX", "-24");
			
			$containerOut.xfFadeOut(50, function()
			{
				if($containerOut.parent().length == 0)
					return false;
				$containerOut.parent().get(0).className = $templateHtml.get(0).className;
				// since everything else is getting destroyed, jump up a bit...
				$container = $containerOut.parent();
				$templateHtml.find('.dark_postrating_container').xfInsert('replaceAll', $containerOut, 'xfFadeIn', 50);
				$container.find('.dark_postrating_inputlist').stop().css({opacity:"1.0"});
			});
			
		});
	});
	
	$(".dark_postrating_hide_post").each(function(){
		if($(this).parents("li.message").hasClass("deleted") || $(this).parents("li.message").hasClass("ignored"))
			return false;
		$(this).parents("li.message").addClass("dark_postrating_hidden").addClass("deleted").addClass("placeholder").append($(this)).children().hide();		
	});
	
	$(".dark_postrating_show_post").live('click', function(e){	
		$(this).parents("li.message").removeClass("dark_postrating_hidden").removeClass("deleted").removeClass("placeholder").children().slideDown(300);
		$(this).parents("li.message").find(".dark_postrating_hide_post").remove();
		return false;
	});
	
});