#include <Account.h>
#include <Transaction.h>
#include <gtest/gtest.h>

TEST(Transaction, Banking){

	const int base_A = 5000, base_B = 5000, base_fee = 100;

	Account Al(0,base_A), Bob(1,base_B);
	Transaction test_tran;

//проверяем конструктор по умолчанию и сеттеры-геттеры
	ASSERT_EQ(test_tran.fee(), 1);
	
	test_tran.set_fee(base_fee);
	ASSERT_EQ(test_tran.fee(), base_fee);

//проверяем случаи когда транзакция не проходит
	ASSERT_THROW(test_tran.Make(Al, Al, 1000), std::logic_error);
	ASSERT_THROW(test_tran.Make(Al, Bob, -50), std::invalid_argument);
	ASSERT_THROW(test_tran.Make(Al, Bob, 50), std::logic_error);
	if (test_tran.fee()*2-1 >= 100)
		ASSERT_EQ(test_tran.Make(Al, Bob, test_tran.fee()*2-1), false);

//проверяем, что всё правильно лочится
	Al.Lock();
	ASSERT_THROW(test_tran.Make(Al, Bob, 1000), std::runtime_error);
	Al.Unlock();

//проверяем что если входные параметры правильные, то транзакция проходит православно
	ASSERT_EQ(test_tran.Make(Al, Bob, 1000), true);
	ASSERT_EQ(Bob.GetBalance(), base_B+1000);	
	ASSERT_EQ(Al.GetBalance(), base_A-1000-base_fee);

//проверяем что транзакция не проходит, если не хватает средств
	ASSERT_EQ(test_tran.Make(Al, Bob, 3900), false);

	//проверяем что баланс не изменился и остался как после прошлой операции
	ASSERT_EQ(Bob.GetBalance(), base_B+1000); 	
	ASSERT_EQ(Al.GetBalance(), base_A-1000-base_fee);
}
