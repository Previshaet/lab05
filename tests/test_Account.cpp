#include <Account.h>
#include <gtest/gtest.h>

TEST(Account, Banking){
	Account test_ac(0, 0); //создаём тестовый объект класса аккаут 
	ASSERT_EQ(test_ac.GetBalance() , 0);
	
	ASSERT_THROW(test_ac.ChangeBalance(100), std::runtime_error);

	test_ac.Lock();
	ASSERT_NO_THROW(test_ac.ChangeBalance(100));
	
	ASSERT_EQ(test_ac.GetBalance() , 100);

	ASSERT_THROW(test_ac.Lock(), std::runtime_error);

	test_ac.Unlock();
	ASSERT_NO_THROW(test_ac.Lock());
}
