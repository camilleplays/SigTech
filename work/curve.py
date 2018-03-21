import matplotlib.pyplot as plt 



# q15 cos 
abs= open("inputdb.txt").readlines()
ord64=open("maxsnr1.txt").readlines()
ord256 =open("maxsnr2.txt").readlines()
ord1024 =open("maxsnr3.txt").readlines()
ord4096 =open("maxsnr4.txt").readlines()

plt.xlabel('input in dB')  
plt.ylabel('max SNR') 
plt.plot(abs,ord64, abs, ord256, abs, ord1024, abs, ord4096)

plt.show()










