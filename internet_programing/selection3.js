$(document).ready(function(){
	"use strict"
	
	$("#button").click(function(){
		var input1 = $("#input1").val();
		var input2 = $("#input2").val();
		
		if(input1 && input2){
			$.ajax("http://headers.jsontest.com/jsontest/"+encodeURIComponent(input1)+"/"+encodeURIComponent(input2)+"/?service=echo",{
				type: "GET",
			}).then(function(data){
				$('#info-div').html("response: "+JSON.stringify(data))
			});
		}else{
			$('#info-div').html("ERROR: input data");
		}
	});
});