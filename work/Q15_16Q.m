abs = [-40.000000, -39.000000, -38.000000, -37.000000, -36.000000, -35.000000, -34.000000, -33.000000, -32.000000, -31.000000, -30.000000, -29.000000, -28.000000, -27.000000, -26.000000, -25.000000, -24.000000, -23.000000, -22.000000, -21.000000, -20.000000, -19.000000, -18.000000, -17.000000, -16.000000, -15.000000, -14.000000, -13.000000, -12.000000, -11.000000, -10.000000, -9.000000, -8.000000, -7.000000, -6.000000, -5.000000, -4.000000, -3.000000, -2.000000, -1.000000];

ord64 = [51.211265, 52.952551, 61.136931, 73.348230, 57.302965, 56.930052, 68.342306, 78.552191, 59.442451, 78.135786, 99.851159, 61.247811, 68.525837, 68.226933, 93.185156, 88.402192, 74.657616, 70.133970, 81.428264, 74.896022, 75.035023, 87.393119, 79.115440, 23.452676, 15.460752, 11.732320, 9.379934, 7.713813, 6.457944, 4.708363, 4.160272, 3.668617, 3.233174, 2.849907, 2.513484, 1.930199, 1.742108, 1.567414, 1.406975, 1.260789];
ord256 = [51.211265, 52.952551, 61.136931, 73.348230, 57.302965, 56.930052, 68.342306, 78.552191, 59.442451, 78.135786, 99.851159, 61.247811, 68.525837, 68.226933, 93.185156, 88.402192, 74.657616, 23.171661, 15.359907, 11.673667, 9.340019, 7.684430, 6.435273, 5.193093, 4.491270, 3.898729, 3.395659, 2.966159, 2.597568, 2.182700, 1.932096, 1.711002, 1.515940, 1.343783, 1.191756, 0.983605, 0.881472, 0.789140, 0.705911, 0.631055];
ord1024 = [51.211265, 52.952551, 61.136931, 73.348230, 57.302965, 56.930052, 68.342306, 78.552191, 59.442451, 78.135786, 99.851159, 22.900089, 15.260455, 11.615545, 9.300381, 7.655215, 6.412715, 5.177381, 4.478037, 3.887524, 3.386117, 2.957990, 2.590540, 2.177216, 1.927257, 1.706733, 1.512173, 1.340457, 1.188818, 0.983374, 0.881007, 0.788529, 0.705217, 0.630322, 0.563105, 0.470123, 0.423211, 0.380447, 0.341602, 0.306418];
ord4096 = [51.211265, 52.952551, 61.136931, 73.348230, 57.302965, 22.637366, 15.162360, 11.557946, 9.261015, 7.626168, 6.390268, 5.350618, 4.591745, 3.963984, 3.438463, 2.994293, 2.615938, 2.266054, 1.992970, 1.755633, 1.548736, 1.367895, 1.209462, 1.051014, 0.933102, 0.828732, 0.736293, 0.654374, 0.581737, 0.501709, 0.447882, 0.399726, 0.356671, 0.318199, 0.283834, 0.245384, 0.219629, 0.196473, 0.175678, 0.157022]

figure
plot(abs,ord64);
xlabel('input DB')
ylabel('max SNR')
hold on
plot(abs,ord256);
hold on
plot(abs,ord1024);
hold on
plot(abs,ord4096);

figure
plot(abs,ord64);
hold on
plot(abs,ord256);
