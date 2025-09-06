let map, marker;

function initMap() {
    // Default location until GPS updates
    map = L.map('map').setView([17.3850, 78.4867], 15); // Hyderabad coords

    L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
        attribution: '&copy; OpenStreetMap contributors'
    }).addTo(map);

    marker = L.marker([17.3850, 78.4867]).addTo(map)
        .bindPopup("VALOR Robot")
        .openPopup();
}

async function updateStatus() {
    try {
        const res = await fetch("/status");
        const data = await res.json();

        // Update command & GPS text
        document.getElementById("cmd").innerText = data.command;
        document.getElementById("gps").innerText =
            `Lat: ${data.gps.lat.toFixed(6)}, Lon: ${data.gps.lon.toFixed(6)}`;

        // Update marker position
        if (marker) {
            marker.setLatLng([data.gps.lat, data.gps.lon]);
            map.setView([data.gps.lat, data.gps.lon]);
        }
    } catch (err) {
        console.error("Error fetching status:", err);
    }
}

// Init map on page load
window.onload = function() {
    initMap();
    setInterval(updateStatus, 1000);
}
