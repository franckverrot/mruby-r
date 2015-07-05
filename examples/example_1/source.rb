class DataSource
  def initialize
    @count = 0
    @elements = (0..100).map { |i| sprintf("e%03d", i) }
  end

  def next
    if @count < 1_000
      @count += 1
      @elements.sample.to_s
    else
      nil
    end
  end
end

DataSource # Don't forget to return the class at the end of the script
