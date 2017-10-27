String DHTtoHTML(float temp, float hum) {
  String message = "<html> \
 <head> \
  <script type='text/javascript' src='https://www.gstatic.com/charts/loader.js'></script> \
  <script type='text/javascript'> \
    google.charts.load('current', {'packages':['gauge']}); \ 
    google.charts.setOnLoadCallback(drawGaugeTemp); \
    google.charts.setOnLoadCallback(drawGaugeHum); \
    function drawGaugeTemp() { \
  var gaugeData = google.visualization.arrayToDataTable([ \
    ['Label', 'Value'], \
    ['Temp C', ";
    
message += String(temp);

message += "] \
  ]); \
  var gaugeOptions = {min: 20, max: 40,  \ 
          yellowFrom: 20, yellowTo: 25, \
    greenFrom: 25, greenTo: 35, \
    redFrom: 35, redTo: 40, \
    minorTicks: 5 \
  }; \
      var gaugeTemp = new google.visualization.Gauge(document.getElementById('gauge_div_temp')); \
      gaugeTemp.draw(gaugeData, gaugeOptions); \
    } \
    function drawGaugeHum() { \
  var gaugeData = google.visualization.arrayToDataTable([ \
    ['Label', 'Value'], \
    ['Hum %', ";
    
message += String(hum);

message += "] \
  ]); \
  var gaugeOptions = {min: 0, max: 100, \ 
          yellowFrom: 0, yellowTo: 40, \
    greenFrom: 40, greenTo: 70, \
    redFrom: 70, redTo: 100, \
    minorTicks: 5 \
  }; \
      var gaugeHum = new google.visualization.Gauge(document.getElementById('gauge_div_hum')); \
      gaugeHum.draw(gaugeData, gaugeOptions); \
    } \
  </script> \
 </head> \
 <body> \
    <table><tr> \
    <td><div id='gauge_div_temp' style='width:280px; height: 280px;'></div></td> \
    <td><div id='gauge_div_hum' style='width:280px; height: 280px;'></div></td> \
    </tr></table> \
</body></html> ";

  return message;
}
