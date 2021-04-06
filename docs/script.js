var request = new XMLHttpRequest();
request.open('GET', "https://onheiron.github.io/birds-vs-bats/demo.gb", true);
request.responseType = 'blob';
request.onload = function() {
    var reader = new FileReader();
    reader.readAsDataURL(request.response);
    reader.onload =  function(e){
        console.log('DataURL:', e.target.result);
    };
};
request.send();