###!----------------------------------------------
###!
###! JOC DE PROVES DE LA CLASSE ITER_SUBSET
###!
###!----------------------------------------------
###!
###!  1. Errors: k > n    
###!  2. n = 1
###!  3. n = 3
###!  4. n = 5
###!  6. operadors == y !=
###!  
###!
###!------------------------------------------------------------------
###1 Error 31: Acces amb iterador de subconjunts invalid
###!------------------------------------------------------------------
###!
#init it iter_subset 1 2
#*
Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
##Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
#end
true
##true
#++
#end
true
##true
#postincr
#end
true
##true
#all_subsets 1 2
Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
##Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
###!
#it destroy
###!
#init it iter_subset 0 1
#end
true
##true
#*
Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
##Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
#++
#end
true
##true
#++
#end
true
##true
#postincr
#end
true
##true
#postincr
#end
true
##true
###!
#it destroy
###!
###!
#init it iter_subset 1 1
#end
false
##false
#*
{1}
##{1}
#++
#*
Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
##Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
###!
#it destroy
###!
#init it iter_subset 1 1
#end
false
##false
#*
{1}
##{1}
#postincr
#*
Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
##Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
###!
#it destroy
###!
#init it iter_subset 5 3
#end
false
##false
#*
{1,2,3}
##{1,2,3}
#++
#++
#postincr
#postincr
#++
#postincr
#++
#postincr
#++
#++
#end
true
##true
#*
Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
##Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
#postincr
#end
true
##true
#*
Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
##Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
#++
#end
true
##true
#*
Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
##Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
###!
#it destroy
###!
###!
###!
###!------------------------------------------------------------------
###2 n = 1
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###2.1 k = 0 
###!------------------------------------------------------------------
###!
#init it iter_subset 1 0
#end
false
##false
#*
{}
##{}
#++
#end
true
##true
#all_subsets 1 0
{}
##{}
###!
#it destroy
###!
#init it iter_subset 1 0
#end
false
##false
#*
{}
##{}
#postincr
#end
true
##true
#all_subsets 1 0
{}
##{}
###!
#it destroy
###!
###!
###!------------------------------------------------------------------
###2.2 k = 1 
###!------------------------------------------------------------------
###!
#init it iter_subset 1 1
#end
false
##false
#*
{1}
##{1}
#++
#end
true
##true
#all_subsets 1 1
{1}
##{1}
###!
#it destroy
###!
#init it iter_subset 1 1
#end
false
##false
#*
{1}
##{1}
#postincr
#end
true
##true
#all_subsets 1 1
{1}
##{1}
###!
#it destroy
###!
###!
###!
###!------------------------------------------------------------------
###3 n = 3 
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###3.1 k = 0 
###!------------------------------------------------------------------
###!
#init it iter_subset 3 0
#end
false
##false
#*
{}
##{}
#++
#end
true
##true
#all_subsets 3 0
{}
##{}
###!
#it destroy
###!
###!
###!------------------------------------------------------------------
###3.2 k = 1 
###!------------------------------------------------------------------
###!
#init it iter_subset 3 1
#end
false
##false
#*
{1}
##{1}
#++
#*
{2}
##{2}
#++
#*
{3}
##{3}
#end
false
##false
#++
#end
true
##true
#all_subsets 3 1
{1}, {2}, {3}
##{1}, {2}, {3}
###!
###!
#it destroy
###!
###!
###!------------------------------------------------------------------
###3.3 k = 2 
###!------------------------------------------------------------------
###!
#init it iter_subset 3 2
#end
false
##false
#*
{1,2}
##{1,2}
#postincr
#end
false
##false
#*
{1,3}
##{1,3}
#postincr
#end
false
##false
#*
{2,3}
##{2,3}
#postincr
#end
true
##true
#all_subsets 3 2
{1,2}, {1,3}, {2,3}
##{1,2}, {1,3}, {2,3}
###!
###!
#it destroy
###!
###!
###!------------------------------------------------------------------
###3.4 k = 3 
###!------------------------------------------------------------------
###!
#init it iter_subset 3 3
#end
false
##false
#*
{1,2,3}
##{1,2,3}
#postincr
#end
true
##true
#postincr
#end
true
##true
#all_subsets 3 3
{1,2,3}
##{1,2,3}
###!
###!
#it destroy
###!
###!
###!
###!------------------------------------------------------------------
###4 n = 5 
###!------------------------------------------------------------------
###!
###!------------------------------------------------------------------
###4.1 k = 0 
###!------------------------------------------------------------------
###!
#init it iter_subset 5 0
#end
false
##false
#*
{}
##{}
#postincr
#end
true
##true
#all_subsets 5 0
{}
##{}
###!
#it destroy
###!
###!
###!------------------------------------------------------------------
###4.2 k = 1 
###!------------------------------------------------------------------
###!
#init it iter_subset 5 1
#end
false
##false
#*
{1}
##{1}
#postincr
#*
{2}
##{2}
#++
#*
{3}
##{3}
#postincr
#*
{4}
##{4}
#postincr
#*
{5}
##{5}
#++
#end
true
##true
#all_subsets 5 1
{1}, {2}, {3}, {4}, {5}
##{1}, {2}, {3}, {4}, {5}
###!
#it destroy
###!
###!
###!------------------------------------------------------------------
###4.3 k = 2 
###!------------------------------------------------------------------
###!
#init it iter_subset 5 2
#end
false
##false
#*
{1,2}
##{1,2}
#++
#*
{1,3}
##{1,3}
#postincr
#*
{1,4}
##{1,4}
#postincr
#*
{1,5}
##{1,5}
#postincr
#*
{2,3}
##{2,3}
#++
#*
{2,4}
##{2,4}
#++
#*
{2,5}
##{2,5}
#++
#*
{3,4}
##{3,4}
#postincr
#*
{3,5}
##{3,5}
#postincr
#*
{4,5}
##{4,5}
#postincr
#end
true
##true
#all_subsets 5 2
{1,2}, {1,3}, {1,4}, {1,5}, {2,3}, {2,4}, {2,5}, {3,4}, {3,5}, {4,5}
##{1,2}, {1,3}, {1,4}, {1,5}, {2,3}, {2,4}, {2,5}, {3,4}, {3,5}, {4,5}
###!
#it destroy
###!
###!
###!------------------------------------------------------------------
###4.4 k = 3 
###!------------------------------------------------------------------
###!
#init it iter_subset 5 3
#end
false
##false
#*
{1,2,3}
##{1,2,3}
#++
#*
{1,2,4}
##{1,2,4}
#++
#*
{1,2,5}
##{1,2,5}
#postincr
#*
{1,3,4}
##{1,3,4}
#postincr
#*
{1,3,5}
##{1,3,5}
#++
#*
{1,4,5}
##{1,4,5}
#++
#*
{2,3,4}
##{2,3,4}
#++
#*
{2,3,5}
##{2,3,5}
#postincr
#*
{2,4,5}
##{2,4,5}
#postincr
#*
{3,4,5}
##{3,4,5}
#postincr
#end
true
##true
#all_subsets 5 3
{1,2,3}, {1,2,4}, {1,2,5}, {1,3,4}, {1,3,5}, {1,4,5}, {2,3,4}, {2,3,5}, {2,4,5}, {3,4,5}
##{1,2,3}, {1,2,4}, {1,2,5}, {1,3,4}, {1,3,5}, {1,4,5}, {2,3,4}, {2,3,5}, {2,4,5}, {3,4,5}
###!
#it destroy
###!
###!
###!------------------------------------------------------------------
###4.5 k = 4 
###!------------------------------------------------------------------
###!
#init it iter_subset 5 4
#end
false
##false
#*
{1,2,3,4}
##{1,2,3,4}
#++
#*
{1,2,3,5}
##{1,2,3,5}
#++
#*
{1,2,4,5}
##{1,2,4,5}
#++
#*
{1,3,4,5}
##{1,3,4,5}
#postincr
#*
{2,3,4,5}
##{2,3,4,5}
#++
#end
true
##true
#all_subsets 5 4
{1,2,3,4}, {1,2,3,5}, {1,2,4,5}, {1,3,4,5}, {2,3,4,5}
##{1,2,3,4}, {1,2,3,5}, {1,2,4,5}, {1,3,4,5}, {2,3,4,5}
###!
#it destroy
###!
###!
###!------------------------------------------------------------------
###4.6 k = 5 
###!------------------------------------------------------------------
###!
#init it iter_subset 5 5
#end
false
##false
#*
{1,2,3,4,5}
##{1,2,3,4,5}
#++
#end
true
##true
#all_subsets 5 5
{1,2,3,4,5}
##{1,2,3,4,5}
###!
#it destroy
###!
###!
###!
###!------------------------------------------------------------------
###6 operadors == y !=
###!------------------------------------------------------------------
###!
#init it1 iter_subset 0 0
#init it2 iter_subset 0 0
###!
#it1 == it2
true
##true
#it1 != it2
false
##false
#it1 *
{}
##{}
#it2 *
{}
##{}
#it1 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
#it1 *
Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
##Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
#it2 *
{}
##{}
#it2 ++
#it1 == it2
true
##true
#it1 != it2
false
##false
#it2 *
Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
##Error::iter_subset:31:Acces amb iterador de subconjunts invalid.
###!
#it1 destroy
#it2 destroy
###!
#init it1 iter_subset 1 0
#init it2 iter_subset 1 0
###!
#it1 == it2
true
##true
#it1 != it2
false
##false
#it2 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
###!
#it1 destroy
#it2 destroy
###!
#init it1 iter_subset 1 0
#init it2 iter_subset 2 0
###!
#it1 == it2
true
##true
#it1 != it2
false
##false
#it2 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
###!
#it1 destroy
#it2 destroy
###!
#init it1 iter_subset 1 1
#init it2 iter_subset 2 1
###!
#it1 == it2
false
##false
#it1 != it2
true
##true
#it1 ++
#it2 ++
#it2 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
###!
#it1 destroy
#it2 destroy
###!
#init it1 iter_subset 2 1
#init it2 iter_subset 3 1
###!
#it1 == it2
false
##false
#it1 != it2
true
##true
#it1 ++
#it2 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
###!
#it1 destroy
#it2 destroy
###!
#init it1 iter_subset 3 1
#init it2 iter_subset 3 2
###!
#it1 == it2
false
##false
#it1 != it2
true
##true
#it1 ++
#it2 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
#it1 ++
#it1 ++
#it2 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
#it2 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
###!
#it1 destroy
#it2 destroy
###!
#init it1 iter_subset 3 2
#init it2 iter_subset 3 2
###!
#it1 == it2
true
##true
#it1 != it2
false
##false
#it1 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
#it1 ++
#it2 ++
#it2 ++
#it1 == it2
true
##true
#it1 != it2
false
##false
#it1 *
{2,3}
##{2,3}
#it2 *
{2,3}
##{2,3}
#it1 ++
#it2 ++
#it1 == it2
true
##true
#it1 != it2
false
##false
###!
#it1 destroy
#it2 destroy
###!
#init it1 iter_subset 5 3
#init it2 iter_subset 5 3
###!
#it1 == it2
true
##true
#it1 != it2
false
##false
#it1 ++
#it1 ++
#it1 ++
#it1 ++
#it1 ++
#it2 ++
#it2 ++
#it2 ++
#it2 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
#it2 ++
#it2 ++
#it2 ++
#it2 ++
#it2 ++
#it1 ++
#it1 ++
#it1 ++
#it1 ++
#it1 == it2
true
##true
#it1 != it2
false
##false
#it1 ++
#it1 == it2
false
##false
#it1 != it2
true
##true
#it2 ++
#it1 == it2
true
##true
#it1 != it2
false
##false
###!
#it1 destroy
#it2 destroy
###!
###!
[0/0]
