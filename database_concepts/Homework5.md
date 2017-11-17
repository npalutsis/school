#Homework 5  
*Name:* Nick Palutsis  
*Date:* November 17, 2017  

##Problem 1  

*a.)* `SELECT COUNT(*) FROM zips;`  
	There are 2,483,448 rows  

*b.)* `SELECT * FROM zips WHERE zip=90210;`  
	It took 0.01 seconds to return 1 result. It was very fast since zip is the primary key, and it was looking for an exact match. This yields only one result, so it does not need to check each row.  

```
SELECT city, stabbr FROM zips order by rand() limit 1;
+----------------+--------+
| city           | stabbr |
+----------------+--------+
| CAMP PENDLETON | CA     |
+----------------+--------+
1 row in set (2.73 sec)
```    

*c.)* `SELECT * FROM zips WHERE city = 'CAMP PENDLETON';`  
	It took 2.07 seconds to return 64 results. C takes longer because it is searching through a non-indexed column, so the database must search each entry for a match. B uses a primary key to search for a unique value, so the database knows directly WHERE to look pretty much thanks to indexing.  

*d.)* `SELECT * FROM zips WHERE city_idx = 'CAMP PENDLETON';`  
	It took 0.00 seconds to return 64 results. D is faster since it searches through an indexed column. Since it is indexed, the database knows the ordering, so it does not need to look row by row like C does. It can effectively skip looking through most of the entries to find the one it needs.  

*e.)* `SELECT * FROM zips WHERE city = 'CAMP PENDLETON';`  
	It took 0.00 seconds to return 64 results. E is faster than in C because the search result was cached. Since it is cahed, the database can simply reoutput the result that is stored instead of searching the database all over again.  

*f.)* `SELECT * FROM zips WHERE city like 'CAMP PENDLE%';`  
	It took 2.07 seconds to return 64 results. It took the same amount of time because the database had to search each entry in both cases since neither query used indexed columns. Both C and F also returned the exact same number of columns, so it makes sense that the query times would be exactly the same.  

*g.)* `SELECT * FROM zips WHERE city_idx like 'CAMP PENDLE%';`  
	It took 0.00 seconds to return 64 results. G is faster since city_idx is an indexed column while city is not. Indexing the column allows the database to avoid searching each entry like in F since the database already knows the ordering.  

*h.)* `SELECT * FROM zips WHERE city LIKE '%ON';`  
	It took 2.66 seconds to return 263,296 results.  

*i.)* `SELECT * FROM zips WHERE city LIKE '%ON';`  
	It took 2.69 seconds to return 263,296 results. H is slightly faster than I, but they are pretty equal. This is because the `LIKE '%ON'` command is not sargable since the percent symbol precedes the string. Even though I is indexed, the database must search each entry due to how the query is structured.  

*j.)* `SELECT COUNT(*) FROM zips WHERE zip > 20000 AND zip < 80000;`  
	It took 0.00 seconds to return 25139 results.  

*k.)* `SELECT COUNT(*) FROM zips WHERE city > 'CAMP PENDLETON';`  
	It took 0.98 seconds to return 2160120 results.  

*l.)* `SELECT COUNT(*) FROM zips WHERE city_idx > 'CAMP PENDLETON';`  
	It took 0.68 seconds to return 2160120 results. L is faster than K since city_idx is an indexed column and city is not. Since most of the entries will fall into the 20,000-80,000 range, most of the entries will inevitably need to be checked which explains why the queries are somewhat close in execution time. However, K will still have to compare **every** entry since it is unindexed, while L only has to compare **most** entries.  

##Problem 2  

*a.)* `SELECT COUNT(*) FROM (SELECT zip FROM zips WHERE city_idx = 'CAMP PENDLETON' AND stabbr = 'CA' AND zip <= 99999) ZIP_CODES, (SELECT zip FROM industry_records) INDUSTRIES WHERE ZIP_CODES.zip = INDUSTRIES.zip;`  
	It took 2.75 seconds to return 61 results.  

*b.)* `SELECT COUNT(*) FROM (SELECT zip FROM zips WHERE city_idx = 'CAMP PENDLETON' AND stabbr = 'CA' AND zip <= 99999) ZIP_CODES, (SELECT zip_idx FROM industry_records) INDUSTRIES WHERE ZIP_CODES.zip = INDUSTRIES.zip_idx;`  
	It took 2.43 seconds to return 61 results.  

*c.)* B performed the query faster than A because even though I am using the city_idx for both queries, only B uses an indexed column. Since the two tables are being joined, A is limited by `industry_records` which is not using an indexed zip code column. Using an indexed column allows the database to join the centries faster since it can more efficiently look up the entries that need joined.  

##Problem 3  

##Problem 4  

*a.)* Yes, consistency is preserved. Even though the consistency is not preserved by `A = A + B` in the middle of the transaction, it only matters if the consistency is preserved at the end. 'B = A + B' restores the consistency since B must now be greater than A.  

*b.)* No, consistenccy is not preserved. `B = A + B` preserveres consistency through the middle of the transaction, but `A = A + B` ruins the consistency since A is no longer less than B.  

*c.)* Yes, consistency is preserved. Even though the consistency is not preserved by `A = B + 1` in the middle of the transaction, it only matters if the consistency is preserved at the end. 'B = A + 1' restores the consistency since B must now be greater than A.  

##Problem 5  
*a.)*  

| Action    | a  | b   | Mem A | Mem B | Disk A | Disk B |
|:----------|:--:|:---:|:-----:|:-----:|:------:|:------:|
| -         | -  | -   | -     | -     | 5      | 10     |
| INPUT(A)  | -  | -   | 5     | -     | 5      | 10     |
| INPUT(B)  | -  | -   | 5     | 10    | 5      | 10     |
| r(A, a)   | 5  | -   | 5     | 10    | 5      | 10     |
| r(B, b)   | 5  | 10  | 5     | 10    | 5      | 10     |
| a = a + b | 15 | 10  | 5     | 10    | 5      | 10     |
| w(A, a)   | 15 | 10  | 15    | 10    | 5      | 10     |
| b = a + b | 15 | 25  | 15    | 10    | 5      | 10     |
| w(B, b)   | 15 | 25  | 15    | 25    | 5      | 10     |
| OUTPUT(B) | 15 | 25  | 15    | 25    | 15     | 10     |
| OUTPUT(A) | 15 | 25  | 15    | 25    | 15     | 25     |

Since B is output first, consistency is preserved even if a crash occurs in between outputs because A will still be less than B. This would not necessarily be the case if B were output after A.  

*b.)*  
| Action    | a  | b   | Mem A | Mem B | Disk A | Disk B |  
|-----------|----|-----|-------|-------|--------|--------|  
| -         | -  | -   | -     | -     | 5      | 10     |  
| INPUT(B)  | -  | -   | -     | 10    | 5      | 10     |  
| INPUT(A)  | -  | -   | 5     | 10    | 5      | 10     |  
| r(B, b)   | -  | 10  | 5     | 10    | 5      | 10     |  
| r(A, a)   | 5  | 10  | 5     | 10    | 5      | 10     |  
| b = a + b | 5  | 15  | 5     | 10    | 5      | 10     |  
| w(B, b)   | 5  | 15  | 5     | 15    | 5      | 10     |  
| a = a + b | 20 | 15  | 5     | 15    | 5      | 10     |  
| w(A, a)   | 20 | 15  | 20    | 15    | 5      | 10     |  
| OUTPUT(B) | 20 | 15  | 20    | 15    | 5      | 15     |  
| OUTPUT(A) | 20 | 15  | 20    | 15    | 20     | 15     |  

The output actions will not preserve the consistency since the transaction itself does not even preserve consistency.  

*c.)*  
| Action    | a  | b  | Mem A | Mem B | Disk A | Disk B |  
|-----------|----|----|-------|-------|--------|--------|  
| -         | -  | -  | -     | -     | 5      | 10     |  
| INPUT(A)  | -  | -  | 5     | -     | 5      | 10     |  
| INPUT(B)  | -  | -  | 5     | 10    | 5      | 10     |  
| r(A, a)   | 5  | -  | 5     | 10    | 5      | 10     |  
| r(B, b)   | 5  | 10 | 5     | 10    | 5      | 10     |  
| a = b + 1 | 11 | 10 | 5     | 10    | 5      | 10     |  
| w(A, a)   | 11 | 10 | 11    | 10    | 5      | 10     |  
| b = a + 1 | 11 | 12 | 11    | 10    | 5      | 10     |  
| w(B, b)   | 11 | 12 | 11    | 12    | 5      | 10     |  
| OUTPUT(B) | 11 | 12 | 11    | 12    | 11     | 10     |  
| OUTPUT(A) | 11 | 12 | 11    | 12    | 11     | 12     |

Since B is output first, consistency is preserved even if a crash occurs in between outputs because A will still be less than B. This would not necessarily be the case if B were output after A.  



| Component          | Control Signal Value |
|--------------------|:--------------------:|
| Write Register Mux |           1          |
| Write Data Mux     |          10          |
| To ALU Input 1 Mux |           1          |
| To ALU Input 2 Mux |      Don't Care      |