$(document).ready(function(){
	"use strict"
	
	$("#button").click(function(){
		var input = $("#input").val();
		
		if(input){
			$.ajax("http://headers.jsontest.com/jsontest?service=md5",{
				type: "POST",
				data: {
					text: input
				}
			}).then(function(data){
				$('#info-div').html("original:"+data.original+" md5:"+data.md5)
			});
		}else{
			$('#info-div').html("ERROR: input data");
		}
	});
});