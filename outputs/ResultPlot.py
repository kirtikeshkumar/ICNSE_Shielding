import matplotlib.pyplot as pl

Energy = [200,400,600,800,1000,1200,1400,1600,1800]
elneu = [10 , 9 , 8 , 14 , 9 , 23 , 45 , 95 , 114 ]
posneu = [1 , 0 , 0 , 0 , 1 , 1 , 3 , 11 , 9]
gamneu = [1014 , 1175 , 1304 , 1419 , 1842 , 2520 , 4102 , 6610 , 9471]
neuneu = [0 , 0 , 0 , 0 , 0 , 1 , 10 , 17 , 47]

elgam = [0 , 0 , 0 , 0 , 0 , 10 , 32 , 72 , 117]
gamgam = [0 , 0 , 0 , 0 , 5 , 14 , 97 , 227 , 452]


pl.yscale('log')
pl.yticks(fontsize=23, weight='bold')
pl.xticks(fontsize=23, weight='bold')
pl.xlim(100.0,1900)
pl.ylim(1.0,15000)
pl.xlabel("Energy (keV)",fontsize=26, weight='bold')
pl.ylabel("Counts",fontsize=26, weight='bold')
pl.title("Particles Reaching the detector volume",fontsize=26, weight='bold')
pl.text(500, 60, 'Incident Particles '+r'$10^7$'+' neutron', fontsize = 26, weight='bold')
pl.plot(Energy,elneu,'bv--',label=r'$e^-$',linewidth=5,markersize=12)#,color='blue',marker='v',linestyle=None)
pl.plot(Energy,posneu,'k^--',label=r'$e^+$',linewidth=5,markersize=12)#,color='black',marker='^',linestyle=None)
pl.plot(Energy,gamneu,'r1--',label=r'$\gamma$',linewidth=5,markersize=12)#,color='red',marker='1',linestyle=None)
pl.plot(Energy,neuneu,'go--',label=r'$n$',linewidth=5,markersize=12)#,color='green',marker='o',linestyle=None)
pl.legend(fontsize=26, loc=0)
pl.show()

pl.yticks(fontsize=23, weight='bold')
pl.xticks(fontsize=23, weight='bold')
pl.xlim(100.0,1900)
pl.ylim(1.0,500)
pl.xlabel("Energy (keV)",fontsize=26, weight='bold')
pl.ylabel("Counts",fontsize=26, weight='bold')
pl.title("Particles Reaching the detector volume",fontsize=26, weight='bold')
pl.text(700, 300, 'Incident Particles '+r'$10^7$'+' '+r'$\gamma$', fontsize = 26, weight='bold')
pl.plot(Energy,elgam,'bv--',label=r'$e^-$',linewidth=5,markersize=12)#,color='blue',marker='v',linestyle=None)
pl.plot(Energy,gamgam,'r1--',label=r'$\gamma$',linewidth=5,markersize=12)#,color='red',marker='1',linestyle=None)
pl.legend(fontsize=26, loc=0)
pl.savefig("PreliminaryGammaShielding.pdf")
pl.savefig("PreliminaryGammaShielding.png")
pl.show()
