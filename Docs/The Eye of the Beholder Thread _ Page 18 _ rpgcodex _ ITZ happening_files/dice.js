
/**
 * We bind to the submit on the dice roll form
 */
!function($, window, document, _undefined)
{

	XenForo.DiceRollForm = function($form) {
		$form.bind('AutoValidationComplete', function(e) {
			// find the postId and template
			var ajaxData = e.ajaxData;
			
			// Append to the end of the post
			var messageNode = $('#post-' + ajaxData.postId + ' .messageMeta');
			messageNode.before(ajaxData.template);
			
			// Activate the children
			var fieldset = $('#dice-' + ajaxData.postId + '-' + ajaxData.boxId);
			fieldset.xfActivate();
		});
	};
	
	XenForo.PickListForm = function($form) {
		$form.bind('AutoValidationComplete', function(e) {
			// find the postId and template
			var ajaxData = e.ajaxData;
			
			// Append to the end of the post
			var messageNode = $('#post-' + ajaxData.postId + ' .messageMeta');
			messageNode.before(ajaxData.template);
		});
	};	
	
	XenForo.ThrowNewDice = function($button) {
		var callback = function(ajaxData, textStatus) {
			if (ajaxData.error) {
				XenForo.hasResponseError(ajaxData, textStatus);
			} else {
				var diceNode = $('#dice-' + ajaxData.postId + '-' + ajaxData.boxId + ' .ThrowNewDice');
				diceNode.before(ajaxData.template);
				// and update the total
				var total = $('#diceLegendTotal-' + ajaxData.postId + '-' + ajaxData.boxId);
				total.html(ajaxData.total);
			}
		};
		
		$button.bind('click', function(e) {
			e.preventDefault();
			XenForo.ajax($button.data('url'), {}, callback);
		});
	};

	var pickListItemOptionNo = 3;
	XenForo.LastPickListItem = function($textfield) {
		$textfield.bind('blur', function(e) {
			var strValue = $.trim($textfield.val());
			if (strValue !== '') {
				var newNode = $('#pickListTemplate').clone().removeAttr('id').css('display', '');
				newNode.find('.optionNo').html(pickListItemOptionNo);
				newNode.find('input').addClass('NextPickListItem');
				pickListItemOptionNo++;

				var optionsNode = $('#pickListOptions'); 
				optionsNode.find('.LastPickListItem').removeClass('LastPickListItem');	// last will not be used anymore
				optionsNode.find('.NextPickListItem').removeClass('NextPickListItem').addClass('LastPickListItem');	// next becomes last
				optionsNode.find('input').unbind('blur');
				optionsNode.append(newNode);
				
				optionsNode.xfActivate();
			}
		});	
	};
	
	XenForo.RpgConfigureCounterForm = function($form) {
		$form.bind('AutoValidationComplete', function(e) {
		
			console.log('Validation complete');
		
			var existing = $('#container_dashboard');
			if (existing.size() > 0) {
				$('#countdown_dashboard').stopCountDown();
				existing.remove();
			};
			 
			var titleBar = $('.titleBar');
			titleBar.after(e.ajaxData.template);
		});
	};	
	
	XenForo.register('#DiceRollForm', 'XenForo.DiceRollForm');
	XenForo.register('#PickListForm', 'XenForo.PickListForm');
	XenForo.register('#RpgConfigureCounterForm', 'XenForo.RpgConfigureCounterForm');
	XenForo.register('button.ThrowNewDice', 'XenForo.ThrowNewDice');
	XenForo.register('input.LastPickListItem', 'XenForo.LastPickListItem');
	
}(jQuery, this, document);

