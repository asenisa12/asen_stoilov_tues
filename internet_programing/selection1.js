$(document).ready(function() {
	"use strict"
	
	$("#button").click(function(){
		var input = $("#input").val();
		
		if(input){
			alert("aa");
			$.ajax("http://headers.jsontest.com/jsontest?service=validate",{
				type: "POST",
				data: {
					json: input
				}
			}).then(function(data) { 
				if (data.error) {
					$('#info-div').html("ERROR: "+data.error);
				} else { 
					$('#info-div').html("This is "+data.object_or_array);
				}
			});
		}
		
	});
});