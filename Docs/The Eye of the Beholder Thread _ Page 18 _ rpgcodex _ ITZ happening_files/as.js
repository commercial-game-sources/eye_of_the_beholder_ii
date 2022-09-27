/**
 * Simple xenForo editor AutoSave
 * Supports WYSIWYG editor and text box editor
 * Requires storage support in browser
 * Author: Adam Oest
 * Version: 0.1
 */
try
{
	var WYSIWYG_EDITOR = 'ctrl_message_html';
	var TEXTAREA_EDITOR = 'ctrl_message';
	var DEBUG = false;

	if (window.localStorage || localStorage) 
	{
		// Returns whether or not given data is "empty"
		function isEmpty(data)
		{
			return (
				data == '' 
				|| data.replace(' ','').length == 0
			);
		}

		// Replaces contents of editor with data
		function writeToEditor()
		{
			if (typeof tinyMCE != 'undefined')
			{
				tinyMCE.execInstanceCommand(WYSIWYG_EDITOR,'mceInsertContent',false,storage.getItem(storageKey));
			}
			else
			{
				$('#' + TEXTAREA_EDITOR).val(storage.getItem(storageKey));
			}
			
			if (DEBUG)
			{
				console.log('AutoSave :: Auto-fetched from storage ' + storageKey);
			}
		}

		// Clears stored data
		function clearStorage()
		{
			storage.removeItem(storageKey);
			
			if (DEBUG)
			{
				console.log('AutoSave :: Cleared cache for ' + storageKey);
			}
		}
	
		// Sets stored data
		function setStorage()
		{
			var data = getData();
			if (!isEmpty(data))
			{
				storage.setItem(storageKey, data);
			}
			else
			{
				clearStorage();
			}
		}

		// Gets text currently in the editor
		function getData()
		{	
			if (typeof tinyMCE != 'undefined')
			{
				return tinyMCE.get(WYSIWYG_EDITOR).getContent();
			}
			else
			{
				return $('#' + TEXTAREA_EDITOR).val();
			}
		}
	
		// Restores text into the editors / registers event handlers
		function insertData()
		{
			if (storage.getItem(storageKey) && isEmpty(getData()))
			{
				writeToEditor();
			}

			if (typeof tinyMCE != 'undefined')
			{
				tinyMCE.get(WYSIWYG_EDITOR).onKeyUp.add(setStorage);
				$('#' + WYSIWYG_EDITOR).parents('form').submit(function(){clearStorage();});
			}
			else
			{
				$('#' + TEXTAREA_EDITOR).keyup(setStorage);
				$('#' + TEXTAREA_EDITOR).parents('form').submit(function(){clearStorage();});
			}	
		}
		
		/* MAIN SCRIPT */

		// Determine URL portion for use as key
		var storage = localStorage || window.localStorage;		
		try
		{
			var urllen = window.location.href.split('/');
			var dl = urllen[0].length + urllen[2].length + 2;
		}
		catch (error)
		{
			var dl = 0;
		}

		var storageKey = window.location.href.slice(dl);
		if (storageKey.indexOf('#') != -1)
		{
			storageKey = storageKey.slice(0, storageKey.indexOf('#'));
		}
		
		// Main exec
		$(document).ready(function(){
			if (typeof tinyMCE != 'undefined')
			{
				tinyMCE.onAddEditor.add(function(mgr,ed){
					tinyMCE.get(ed.id).onInit.add(function(){					
						insertData();
					});
				});
			}
			else
			{
				insertData();
			}
		});
	}
}
catch (err) 
{ 
	console.log('AutoSave :: Error ' + err);
}
