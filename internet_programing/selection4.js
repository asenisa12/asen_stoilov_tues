$(document).ready(function() {
	"use strict"
	
	$("#add").click(function() {
		var key = $("#key").val();
		var value = $("#value").val();
		if (!key || !value) {
			$("#result").html("<li><b>Error:</b> Enter header name and header value</li>");

			return;
		}
		
		var headers = {};
		headers[key] = value;
		$.ajax("http://localhost:18080/jsontest?service=headers", {
			  method: "GET",
			  headers: headers
			}).then(processResponse, handleError);
	});
	function handleError(error) {
		alert(error);
		console.error("error", error, arguments);
	}
	
	function appendToList(list, a, b) {
		var newElement = $("<li/>");
		newElement.html("<b>"+ a + "</b>: " + b);
		list.append(newElement);
	}
	function processResponse(response) {
		$("#result").html("");
		var list = $("#result");
		$.each(response, function(a, b) {
			appendToList(list, a, b);
		});
	}
});