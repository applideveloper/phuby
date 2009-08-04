require 'helper'

class TestRuntime < Phuby::TestCase
  def test_start_stop
    rt = Phuby::Runtime.instance
    rt.start
    rt.stop
    rt.start
    rt.stop
  end

  def test_mutex_lock
    rt = Phuby::Runtime.instance
    rt.start

    assert_raises ThreadError do
      rt.start
    end

  ensure
    rt.stop
  end

  def test_eval_without_start
    rt = Phuby::Runtime.instance
    assert_raises Phuby::Runtime::NotStartedError do
      rt.eval('$foo = 10;')
    end
  end

  def test_get_without_start
    rt = Phuby::Runtime.instance
    assert_raises Phuby::Runtime::NotStartedError do
      rt['foo']
    end
  end

  def test_set_without_start
    rt = Phuby::Runtime.instance
    assert_raises Phuby::Runtime::NotStartedError do
      rt['foo'] = 'bar'
    end
  end

  def test_eval_php_block
    Phuby::Runtime.instance.php do |php|
      php.eval('$foo = 10;')
      assert_equal 10, php['foo']
    end
  end
end
